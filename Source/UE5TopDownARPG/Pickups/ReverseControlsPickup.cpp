// Fill out your copyright notice in the Description page of Project Settings

#include "ReverseControlsPickup.h"
#include "../UE5TopDownARPGCharacter.h"
#include "../MoneyHeistPlayerState.h"
#include "Kismet/GameplayStatics.h"

void AReverseControlsPickup::OnPickup(AUE5TopDownARPGCharacter* Character)
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
		AMoneyHeistPlayerState* PlayerState = Cast<AMoneyHeistPlayerState>(RandomActor->GetPlayerState());
		if (IsValid(PlayerState)) 
		{
			World->GetTimerManager().SetTimer(EffectStopTimerHandle, FTimerDelegate::CreateLambda([this, PlayerState]() { OnEffectStop(PlayerState); }), EffectDuration, false);

			PlayerState->bAreControlsReversed = true;
		}
	}
}

void AReverseControlsPickup::OnEffectStop(AMoneyHeistPlayerState* PlayerState)
{
	PlayerState->bAreControlsReversed = false;
}