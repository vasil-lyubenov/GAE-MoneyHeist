// Fill out your copyright notice in the Description page of Project Settings.

#include "ScorePickup.h"
#include "../UE5TopDownARPGCharacter.h"

void AScorePickup::OnPickup(AUE5TopDownARPGCharacter* Character)
{
	Character->UpdateScore(ScoreIncrease);
}
