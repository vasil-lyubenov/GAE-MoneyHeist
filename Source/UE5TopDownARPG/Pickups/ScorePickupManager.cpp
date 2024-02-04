// Fill out your copyright notice in the Description page of Project Settings.

#include "ScorePickupManager.h"
#include "ScorePickup.h"

AActor* AScorePickupManager::CreateObject()
{
	AActor* SpawnedObject = Super::CreateObject();
	if (IsValid(SpawnedObject))
	{
		int32 PositionSpawned = RandomSpawnLocationIndex;
		AScorePickup* SpawnedScorePickup = Cast<AScorePickup>(SpawnedObject);
		if (IsValid(SpawnedScorePickup))
		{
			TakenPositions.Add(RandomSpawnLocationIndex);
			SpawnedScorePickup->OnPickupCallback.BindLambda([this, PositionSpawned]() { ServerRPC_RemoveObjectAt(PositionSpawned); });
			return SpawnedScorePickup;
		}
	}
	return nullptr;
}