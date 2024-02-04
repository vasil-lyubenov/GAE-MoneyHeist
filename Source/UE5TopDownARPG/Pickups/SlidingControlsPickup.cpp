// Fill out your copyright notice in the Description page of Project Settings.

#include "SlidingControlsPickup.h"
#include "../UE5TopDownARPGCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"

void ASlidingControlsPickup::OnPickup(AUE5TopDownARPGCharacter* Character)
{
	TArray<AActor*> AllCharacters;
	UWorld* World = GetWorld();
	UGameplayStatics::GetAllActorsOfClass(World, AUE5TopDownARPGCharacter::StaticClass(), AllCharacters);

	for (int i = 0; i < AllCharacters.Num(); i++)
	{
		AllCharacters.Remove(Character);
	}

	if (AllCharacters.Num() <= 0)
	{
		return;
	}

	AUE5TopDownARPGCharacter* RandomActor = Cast<AUE5TopDownARPGCharacter>(AllCharacters[FMath::RandRange(0, AllCharacters.Num() - 1)]);
	if (IsValid(RandomActor))
	{
		UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(RandomActor->GetMovementComponent());
		if (MovementComponent)
		{
			float PreviousFriction = MovementComponent->GroundFriction;
			float BreakingDecelWalking = MovementComponent->BrakingDecelerationWalking;
			MovementComponent->GroundFriction = SlidingGroundFriction;
			MovementComponent->BrakingDecelerationWalking = BreakingDeceleration;

			World->GetTimerManager().SetTimer(EffectStopTimerHandle, FTimerDelegate::CreateLambda([this, MovementComponent, PreviousFriction, BreakingDecelWalking]() { MovementComponent->GroundFriction = PreviousFriction; MovementComponent->BrakingDecelerationWalking = BreakingDecelWalking; }), EffectDuration, false);
		}
	}
}