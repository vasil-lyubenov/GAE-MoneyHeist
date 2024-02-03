// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ScorePickup.h"
#include "Engine/StaticMeshActor.h"
#include "ScorePickupManager.generated.h"

UCLASS()
class UE5TOPDOWNARPG_API AScorePickupManager : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AScorePickup>> ScorePickupClasses;

	UPROPERTY(EditDefaultsOnly)
	float SpawnPickupDelay = 2.0f;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSoftObjectPtr<AActor>> ScorePickupPoints;

	// Sets default values for this actor's properties
	AScorePickupManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle CustomSpawnTickTimerHandle;

	UFUNCTION(Server, Reliable)
	void ServerRPC_ClearPickupAt(int32 position);

	UFUNCTION(Server, Reliable)
	void ServerRPC_InitSpawnTimer();
	
	UFUNCTION(Server, Reliable)
	void ServerRPC_CreatePickup();
public:	

	// Return equal to -1 means there is not place available to spawn
	int32 GetRandomPositionToSpawn();

	// Used to stop spawning after game has ended
	UFUNCTION(Server, Reliable)
	void ServerRPC_OnGameEnd();
private:
	TArray<AScorePickup> ScorePickups;

	TSet<int32> TakenPositions;
};
