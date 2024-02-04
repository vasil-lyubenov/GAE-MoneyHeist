// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickup.h"
#include "TimerManager.h"
#include "ReverseControlsPickup.generated.h"

UCLASS()
class UE5TOPDOWNARPG_API AReverseControlsPickup : public ABasePickup
{
	GENERATED_BODY()

	virtual void OnPickup(class AUE5TopDownARPGCharacter* Character) override;

public:
	UPROPERTY(EditDefaultsOnly)
	float EffectDuration = 2.0f;

protected:
	FTimerHandle EffectStopTimerHandle;

	virtual void OnEffectStop(class AMoneyHeistPlayerState* PlayerState);
};