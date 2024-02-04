// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnManager.h"
#include "HazardSpawnManager.generated.h"

UCLASS()
class UE5TOPDOWNARPG_API AHazardSpawnManager : public ASpawnManager
{
	GENERATED_BODY()

protected:
	virtual AActor* CreateObject() override;
};