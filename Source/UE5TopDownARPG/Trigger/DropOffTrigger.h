// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseTrigger.h"
#include "DropOffTrigger.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API ADropOffTrigger : public ABaseTrigger
{
	GENERATED_BODY()
	
protected:
	void ActionStart(AActor* ActorInRange) override;
};
