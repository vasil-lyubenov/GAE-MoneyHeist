// Fill out your copyright notice in the Description page of Project Settings.


#include "ScorePickupManager.h"

// Sets default values
AScorePickupManager::AScorePickupManager()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AScorePickupManager::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(CustomSpawnTickTimerHandle, this, &AScorePickupManager::CreatePickup, SpawnPickupDelay, true);
}

void AScorePickupManager::CreatePickup()
{
	UE_LOG(LogTemp, Warning, TEXT("Spawning score pickup"));
	int32 RandomActorIndex = FMath::RandRange(0, ScorePickupClasses.Num() - 1);
	int32 RandomLocationIndex = FMath::RandRange(0, ScorePickupPoints.Num() - 1);
	GetWorld()->SpawnActor<AActor>(ScorePickupClasses[RandomActorIndex], ScorePickupPoints[RandomLocationIndex]->GetActorLocation(), FRotator::ZeroRotator);
}

void AScorePickupManager::OnGamEnd() 
{
	GetWorld()->GetTimerManager().ClearTimer(CustomSpawnTickTimerHandle);
}
