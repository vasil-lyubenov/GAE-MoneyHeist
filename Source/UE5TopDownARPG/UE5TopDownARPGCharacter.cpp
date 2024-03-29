// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5TopDownARPGCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Abilities/BaseAbility.h"
#include "UE5TopDownARPGGameMode.h"
#include "UE5TopDownARPGPlayerController.h"
#include "UE5TopDownARPG.h"
#include "UI/HealthbarWidget.h"
#include "Net/UnrealNetwork.h"
#include "MoneyHeistPlayerState.h"
#include "Pickups/ScorePickup.h"
#include "MoneyHeistMovementComponent.h"

AUE5TopDownARPGCharacter::AUE5TopDownARPGCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetCastShadow(false);
	WidgetComponent->SetReceivesDecals(false);
	WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WidgetComponent->SetupAttachment(RootComponent);

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	OnTakeAnyDamage.AddDynamic(this, &AUE5TopDownARPGCharacter::TakeAnyDamage);
}

void AUE5TopDownARPGCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (IsValid(WidgetComponent->GetWidgetClass()))
	{
		WidgetComponent->InitWidget();
		HealthbarWidget = Cast<UHealthbarWidget>(WidgetComponent->GetUserWidgetObject());
	}
}

void AUE5TopDownARPGCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnPosition = GetActorLocation();

	if (AbilityTemplate != nullptr)
	{
		AbilityInstance = NewObject<UBaseAbility>(this, AbilityTemplate);
	}
	if (IsValid(HealthbarWidget))
	{
		float HealthPercent = Health / MaxHealth;
		HealthbarWidget->SetPercent(HealthPercent);
	}
}

void AUE5TopDownARPGCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}

void AUE5TopDownARPGCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AUE5TopDownARPGCharacter, Health);
	DOREPLIFETIME(AUE5TopDownARPGCharacter, MaxHealth);
}

bool AUE5TopDownARPGCharacter::ActivateAbility(FVector Location)
{
	AMoneyHeistPlayerState* State = Cast<AMoneyHeistPlayerState>(GetPlayerState());
	if (IsValid(State) && IsValid(AbilityInstance) && State->BombAmount > 0)
	{
		State->BombAmount--;
		return AbilityInstance->Activate(Location);
	}
	return false;
}

void AUE5TopDownARPGCharacter::SetScore(float Score)
{
	HealthbarWidget->SetText(Score);
}

void AUE5TopDownARPGCharacter::TakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigateBy, AActor* DamageCauser)
{
	Health -= Damage;
	OnRep_SetHealth(Health + Damage);
	
	if (Health <= 0.0f)
	{
		Death();
	}
}

void AUE5TopDownARPGCharacter::OnRep_SetHealth(float OldHealth)
{
	if (IsValid(HealthbarWidget))
	{
		float HealthPercent = Health / MaxHealth;
		HealthbarWidget->SetPercent(HealthPercent);
	}

	/*if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Health %f"), Health));
	}*/
}

void AUE5TopDownARPGCharacter::ServerRPC_UpdateState_Implementation(AScorePickup* Pickup)
{
	AMoneyHeistPlayerState* State = Cast<AMoneyHeistPlayerState>(GetPlayerState());
	if (IsValid(State) == false)
	{
		return;
	}

	State->AddItem(Pickup);
}
	

void AUE5TopDownARPGCharacter::RespawnPlayer()
{
	Health = MaxHealth;
	OnRep_SetHealth(0.0f);
	SetActorLocation(SpawnPosition);
}

void AUE5TopDownARPGCharacter::Death()
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("Death"));
	RespawnPlayer();
}
