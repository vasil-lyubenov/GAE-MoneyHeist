// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5TopDownARPGPlayerController.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "UE5TopDownARPGCharacter.h"
#include "UE5TopDownARPGHUD.h"
#include "Engine/World.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "UE5TopDownARPG.h"
#include "MoneyHeistPlayerState.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MoneyHeistMovementComponent.h"

AUE5TopDownARPGPlayerController::AUE5TopDownARPGPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AUE5TopDownARPGPlayerController::OnPlayerDied()
{
	AUE5TopDownARPGHUD* HUD = Cast<AUE5TopDownARPGHUD>(GetHUD());
	if (IsValid(HUD))
	{
		HUD->ShowEndGameScreen();
	}
}

void AUE5TopDownARPGPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void AUE5TopDownARPGPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AUE5TopDownARPGPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AUE5TopDownARPGPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AUE5TopDownARPGPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AUE5TopDownARPGPlayerController::OnSetDestinationReleased);

		EnhancedInputComponent->BindAction(ActivateAbilityAction, ETriggerEvent::Started, this, &AUE5TopDownARPGPlayerController::OnActivateAbilityStarted);

		// Setup touch input events
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Started, this, &AUE5TopDownARPGPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Triggered, this, &AUE5TopDownARPGPlayerController::OnTouchTriggered);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Completed, this, &AUE5TopDownARPGPlayerController::OnTouchReleased);
		EnhancedInputComponent->BindAction(SetDestinationTouchAction, ETriggerEvent::Canceled, this, &AUE5TopDownARPGPlayerController::OnTouchReleased);
	}
}

void AUE5TopDownARPGPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void AUE5TopDownARPGPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();
	
	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;
	bool bHitSuccessful = false;
	if (bIsTouch)
	{
		bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
	}
	else
	{
		bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
	}

	// If we hit a surface, cache the location
	if (bHitSuccessful)
	{
		CachedDestination = Hit.Location;

		AMoneyHeistPlayerState* State = Cast<AMoneyHeistPlayerState>(PlayerState);
		// Logic for reversing controlls
		if (IsValid(State))
		{
			if (State->AreControlsReversed())
			{
				FVector Location = GetPawn()->GetActorLocation();
				CachedDestination = Location + (Location - Hit.Location);
			}
		}
	}
	
	APawn* ControlledPawn = GetPawn();

	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0f, false);
	}
}

void AUE5TopDownARPGPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		FVector Location = GetPawn()->GetActorLocation();

		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

// Triggered every frame when the input is held down
void AUE5TopDownARPGPlayerController::OnTouchTriggered()
{
	bIsTouch = true;
	OnSetDestinationTriggered();
}

void AUE5TopDownARPGPlayerController::OnTouchReleased()
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void AUE5TopDownARPGPlayerController::OnActivateAbilityStarted()
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("OnActivateAbilityStarted"));

	AUE5TopDownARPGCharacter* ARPGCharacter = Cast<AUE5TopDownARPGCharacter>(GetPawn());
	if (IsValid(ARPGCharacter))
	{
		FHitResult Hit;
		bool bHitSuccessful = false;
		if (bIsTouch)
		{
			bHitSuccessful = GetHitResultUnderFinger(ETouchIndex::Touch1, ECollisionChannel::ECC_Visibility, true, Hit);
		}
		else
		{
			bHitSuccessful = GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit);
		}

		// If we hit a surface, cache the location
		if (bHitSuccessful)
		{
			ARPGCharacter->ActivateAbility(Hit.Location);
		}
	}
}

void AUE5TopDownARPGPlayerController::AdjustSpeedByState()
{	
	APawn* MHPawn = GetPawn();
	if (IsValid(MHPawn) == false)
	{
		return;
	}

	APlayerState* MHPlayerState = MHPawn->GetPlayerState();
	if (IsValid(MHPlayerState) == false)
	{
		return;
	}

	AMoneyHeistPlayerState* State = Cast<AMoneyHeistPlayerState>(MHPlayerState);
	if (IsValid(State) == false)
	{
		return;
	}

	UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(GetPawn()->GetMovementComponent());
	if (MovementComponent)
	{
		MovementComponent->MaxWalkSpeed = State->DefaultWalkingSpeed * FMath::Clamp(1.0f - State->Weight, 0.1f, 1.0f);
	}	
}