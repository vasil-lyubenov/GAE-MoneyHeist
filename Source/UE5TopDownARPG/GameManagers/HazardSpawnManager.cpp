// Fill out your copyright notice in the Description page of Project Settings.

#include "HazardSpawnManager.h"
#include "../Hazards/BaseHazard.h"

AActor* AHazardSpawnManager::CreateObject()
{
	AActor* SpawnedObject = Super::CreateObject();
	if (IsValid(SpawnedObject))
	{
		int32 PositionSpawned = RandomSpawnLocationIndex;
		ABaseHazard* SpawnedScorePickup = Cast<ABaseHazard>(SpawnedObject);
		if (IsValid(SpawnedScorePickup))
		{
			TakenPositions.Add(PositionSpawned);
			SpawnedScorePickup->OnRemovedCallback.BindLambda([this, PositionSpawned]() { ServerRPC_RemoveObjectAt(PositionSpawned); });
			return SpawnedScorePickup;
		}
	}
	return nullptr;
}