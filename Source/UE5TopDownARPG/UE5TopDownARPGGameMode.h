// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TimerManager.h"
#include "UE5TopDownARPGGameMode.generated.h"

UCLASS(minimalapi)
class AUE5TopDownARPGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	float GameDuration = 120.0f;

	AUE5TopDownARPGGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION(Server, Reliable)
	void ServerRPC_StartGameTimer();

	void EndGame();

	void MHStopSpawners();

protected:
	FTimerHandle EndGameTimerHandle;
};