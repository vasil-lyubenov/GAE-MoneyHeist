// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "ScorePickup.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API AScorePickup : public ABasePickup
{
	GENERATED_BODY()
	
protected:
	virtual void OnPickup(class AUE5TopDownARPGCharacter* Character);

	UPROPERTY(EditDefaultsOnly)
	float ScoreIncrease = 10.0f;

	UPROPERTY(EditDefaultsOnly)
	float Weight = 10.0f;
};
