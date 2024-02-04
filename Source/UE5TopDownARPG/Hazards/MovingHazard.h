// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseHazard.h"
#include <Net/UnrealNetwork.h>
#include "MovingHazard.generated.h"

UCLASS()
class UE5TOPDOWNARPG_API AMovingHazard : public ABaseHazard
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Server, Reliable)
	void ServerRPC_MoveHazard(float DeltaTime);

	UFUNCTION(Server, Reliable)
	void ServerRPC_InitializeHazardOffset();

protected:
	UPROPERTY(EditDefaultsOnly, Replicated)
	float MovementSpeed = 10.0f;

	UPROPERTY(EditDefaultsOnly)
	float MaxDistance = 1000.0f;

private:
	UPROPERTY(ReplicatedUsing = OnRep_DistanceTraveled)
	float DistanceTraveled = 0.0f;

	UPROPERTY(ReplicatedUsing = OnRep_DistanceTraveled)
	float InitialOffset;

	UFUNCTION()
	void OnRep_DistanceTraveled();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
