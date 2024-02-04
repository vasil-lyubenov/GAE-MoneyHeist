// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE5TopDownARPGGameMode.h"
#include "UE5TopDownARPGPlayerController.h"
#include "UE5TopDownARPGCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "UE5TopDownARPG.h"
#include "MoneyHeistPlayerState.h"
#include "Kismet/GameplayStatics.h"


AUE5TopDownARPGGameMode::AUE5TopDownARPGGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AUE5TopDownARPGPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}

void AUE5TopDownARPGGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	// if somebody new connects restart the game
	GetWorldTimerManager().ClearTimer(EndGameTimerHandle);

	ServerRPC_StartGameTimer();
}

void AUE5TopDownARPGGameMode::ServerRPC_StartGameTimer_Implementation()
{
	GetWorld()->GetTimerManager().SetTimer(EndGameTimerHandle, this, &AUE5TopDownARPGGameMode::EndGame, GameDuration, false);
}

void AUE5TopDownARPGGameMode::EndGame() const
{
	TArray<AActor*> AllCharacters;
	UWorld* World = GetWorld();
	UGameplayStatics::GetAllActorsOfClass(World, AMoneyHeistPlayerState::StaticClass(), AllCharacters);

	if (AllCharacters.Num() <= 0)
	{
		return;
	}

	float MaxScore = 0;
	int32 WinnerIndex = 0;

	for (int i = 0; i < AllCharacters.Num(); i++)
	{
		AMoneyHeistPlayerState* CurrentState = Cast<AMoneyHeistPlayerState>(AllCharacters[i]);
		if (IsValid(CurrentState) && CurrentState->GetScore() > MaxScore)
		{
			MaxScore = CurrentState->GetScore();
			WinnerIndex = i;
		}
	}

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Winner is %s"), *AllCharacters[WinnerIndex]->GetName()));
	}
}