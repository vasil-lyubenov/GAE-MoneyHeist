// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

DECLARE_DELEGATE(OnPickupDelegate)

UCLASS()
class UE5TOPDOWNARPG_API ABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	OnPickupDelegate OnPickupCallback;

	ABasePickup();
protected:
	virtual void OnPickup(class AUE5TopDownARPGCharacter* Character);

	UFUNCTION(Server, Reliable)
	void ServerRPC_OnPickup(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* SphereComponent;
};
