// Fill out your copyright notice in the Description page of Project Settings.


#include "ScorePickupManager.h"
#include "ScorePickup.h"

// Sets default values
AScorePickupManager::AScorePickupManager()
{
	SetReplicates(true);

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AScorePickupManager::BeginPlay()
{
	Super::BeginPlay();

	ServerRPC_InitSpawnTimer();
}

void AScorePickupManager::ServerRPC_ClearPickupAt_Implementation(int32 position)
{
	if (TakenPositions.Contains(position))
	{
		TakenPositions.Remove(position);
	}
}

void AScorePickupManager::ServerRPC_InitSpawnTimer_Implementation()
{
	GetWorld()->GetTimerManager().SetTimer(CustomSpawnTickTimerHandle, this, &AScorePickupManager::ServerRPC_CreatePickup, SpawnPickupDelay, true);
}

void AScorePickupManager::ServerRPC_CreatePickup_Implementation()
{
	int32 RandomActorIndex = FMath::RandRange(0, ScorePickupClasses.Num() - 1);
	int32 RandomLocationIndex = GetRandomPositionToSpawn();

	// No available positions to spawn
	if (RandomLocationIndex == -1)
	{
		return;
	}

	//Check if we can spawn on the following space
	AActor* SpawnedObject = GetWorld()->SpawnActor<AActor>(ScorePickupClasses[RandomActorIndex], ScorePickupPoints[RandomLocationIndex]->GetActorLocation(), FRotator::ZeroRotator);
	if (IsValid(SpawnedObject))
	{
		TakenPositions.Add(RandomLocationIndex);
		AScorePickup* SpawnedScorePickup = Cast<AScorePickup>(SpawnedObject);
		if (IsValid(SpawnedScorePickup))
		{
			//ScorePickups->OnPickupCallback.BindRaw(&OnGameEnd, true, 20);

			SpawnedScorePickup->OnPickupCallback.BindLambda([this, RandomLocationIndex]() { ServerRPC_ClearPickupAt(RandomLocationIndex); });
		}
	}
}

int32 AScorePickupManager::GetRandomPositionToSpawn()
{
	// No point in iterating over elements if sizes are equal
	if (ScorePickupPoints.Num() == TakenPositions.Num()) 
	{
		return -1;
	}

	TArray<int32> AvailableSpots;
	for (int i = 0; i < ScorePickupPoints.Num(); i++) 
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

void AScorePickupManager::ServerRPC_OnGameEnd_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(CustomSpawnTickTimerHandle);
}
