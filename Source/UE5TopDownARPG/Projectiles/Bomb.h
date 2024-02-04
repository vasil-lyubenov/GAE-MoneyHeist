// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bomb.generated.h"

UCLASS()
class UE5TOPDOWNARPG_API ABomb : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABomb();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	float Radius = 200.0f;
	
	UPROPERTY(EditDefaultsOnly)
	float Damage = 100.0f;

	UPROPERTY(EditDefaultsOnly)
	float DetonationTime;
protected:
	FTimerHandle DetonationTimerHandle;

private:
	void DrawDangerZone();

	void Explode();
};
