// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../GameManagers/SpawnManager.h"
#include "ScorePickupManager.generated.h"

UCLASS()
class UE5TOPDOWNARPG_API AScorePickupManager : public ASpawnManager
{
	GENERATED_BODY()

protected:
	virtual AActor* CreateObject() override;
};
