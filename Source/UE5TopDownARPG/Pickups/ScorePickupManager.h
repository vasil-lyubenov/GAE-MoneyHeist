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

public:	
	void CreatePickup();

	// Used to stop spawning after game has ended
	void OnGamEnd();

private:
	TArray<AScorePickup> ScorePickups;
};
