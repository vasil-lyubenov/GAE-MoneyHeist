// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnManager.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
	bReplicates = true;

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();

	ServerRPC_InitSpawnTimer();
}

void ASpawnManager::RemoveObjectAt(int32 position)
{
	if (TakenPositions.Contains(position))
	{
		TakenPositions.Remove(position);
	}
}

AActor* ASpawnManager::CreateObject()
{
	int32 RandomActorIndex = FMath::RandRange(0, SpawnedObjectClasses.Num() - 1);
	RandomSpawnLocationIndex = GetRandomPositionToSpawn();

	// No available positions to spawn
	if (RandomSpawnLocationIndex == -1)
	{
		return nullptr;
	}

	//Check if we can spawn on the following space
	AActor* SpawnedObject = GetWorld()->SpawnActor<AActor>(SpawnedObjectClasses[RandomActorIndex], SpawnPoints[RandomSpawnLocationIndex]->GetActorLocation(), SpawnPoints[RandomSpawnLocationIndex]->GetActorRotation());
	if (IsValid(SpawnedObject))
	{
		return SpawnedObject;
	}

	return nullptr;
}

void ASpawnManager::ServerRPC_RemoveObjectAt_Implementation(int32 position)
{
	RemoveObjectAt(position);
}

void ASpawnManager::ServerRPC_InitSpawnTimer_Implementation()
{
	GetWorld()->GetTimerManager().SetTimer(CustomSpawnTickTimerHandle, this, &ASpawnManager::ServerRPC_CreateObject, SpawnPickupDelay, true);
}

void ASpawnManager::ServerRPC_CreateObject_Implementation()
{
	CreateObject();
}

int32 ASpawnManager::GetRandomPositionToSpawn()
{
	if (bCanAlwaysSpawn)
	{
		return FMath::RandRange(0, SpawnPoints.Num() - 1);
	}

	// No point in iterating over elements if sizes are equal
	if (SpawnPoints.Num() == TakenPositions.Num())
	{
		return -1;
	}

	TArray<int32> AvailableSpots;
	for (int i = 0; i < SpawnPoints.Num(); i++)
	{
		if (!TakenPositions.Contains(i))
		{
			AvailableSpots.Add(i);
		}
	}

	if (AvailableSpots.Num() == 0)
	{
		return -1;
	}

	return AvailableSpots[FMath::RandRange(0, AvailableSpots.Num() - 1)];
}

void ASpawnManager::ServerRPC_OnGameEnd_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(CustomSpawnTickTimerHandle);
}