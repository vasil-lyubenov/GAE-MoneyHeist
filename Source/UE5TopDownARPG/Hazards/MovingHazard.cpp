// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingHazard.h"

void AMovingHazard::BeginPlay()
{
    Super::BeginPlay();

    ServerRPC_InitializeHazardOffset();
}

void AMovingHazard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    ServerRPC_MoveHazard(DeltaTime);
}

void AMovingHazard::ServerRPC_InitializeHazardOffset_Implementation()
{
    InitialOffset = GetActorLocation();
}

void AMovingHazard::ServerRPC_MoveHazard_Implementation(float DeltaTime)
{
    // A correction if we surpass MaxDistanceTraveled by having larger TimeDelta value
    DistanceTraveled = FMath::Min(DistanceTraveled + MovementSpeed * DeltaTime, MaxDistance);

    OnRep_DistanceTraveled();
}

void AMovingHazard::OnRep_DistanceTraveled()
{
    FVector MovePosition = InitialOffset + GetActorForwardVector() * DistanceTraveled;
    SetActorRelativeLocation(MovePosition);
    
    if (DistanceTraveled >= MaxDistance)
    {
        Destroy(true);
    }
}

void AMovingHazard::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AMovingHazard, DistanceTraveled);
    DOREPLIFETIME(AMovingHazard, MovementSpeed);
    DOREPLIFETIME(AMovingHazard, InitialOffset);
}