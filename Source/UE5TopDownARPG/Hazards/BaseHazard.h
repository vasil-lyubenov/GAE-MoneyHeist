// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseHazard.generated.h"

DECLARE_DELEGATE(OnHazardRemovedDelegate)

UCLASS()
class UE5TOPDOWNARPG_API ABaseHazard : public AActor
{
	GENERATED_BODY()
	
public:	
	OnHazardRemovedDelegate OnRemovedCallback;

	ABaseHazard();

protected:
	virtual void BeginPlay() override;

	virtual void Destroyed() override;

	UPROPERTY(EditDefaultsOnly)
	float Damage = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* BoxComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ActionStart(class AUE5TopDownARPGCharacter* Character);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
