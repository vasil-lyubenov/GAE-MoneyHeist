// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "BombPickup.generated.h"

UCLASS()
class UE5TOPDOWNARPG_API ABombPickup : public ABasePickup
{
	GENERATED_BODY()
	
	virtual void OnPickup(class AUE5TopDownARPGCharacter* Character) override;

public:
	UPROPERTY(EditDefaultsOnly)
	int32 BombIncreaseAmount = 1;
};
