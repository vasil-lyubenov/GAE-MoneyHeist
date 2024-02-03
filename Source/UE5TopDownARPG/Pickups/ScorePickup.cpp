// Fill out your copyright notice in the Description page of Project Settings.

#include "ScorePickup.h"
#include "../UE5TopDownARPGCharacter.h"

void AScorePickup::OnPickup(AUE5TopDownARPGCharacter* Character)
{
	Super::OnPickup(Character);
	Character->UpdateScore(ScoreIncrease);
}

float AScorePickup::GetWeight()
{
	return Weight;
}

float AScorePickup::GetScore()
{
	return ScoreIncrease;
}

void AScorePickup::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AScorePickup, ScoreIncrease);
	DOREPLIFETIME(AScorePickup, Weight);
}