// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReverseControlsPickup.h"
#include "SlidingControlsPickup.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API ASlidingControlsPickup : public AReverseControlsPickup
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	float SlidingGroundFriction = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	float BreakingDeceleration = 350.0f;

	virtual void OnPickup(class AUE5TopDownARPGCharacter* Character) override;
};