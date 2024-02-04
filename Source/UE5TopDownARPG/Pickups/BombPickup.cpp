// Fill out your copyright notice in the Description page of Project Settings.

#include "BombPickup.h"
#include "../UE5TopDownARPGCharacter.h"
#include "../MoneyHeistPlayerState.h"

void ABombPickup::OnPickup(AUE5TopDownARPGCharacter* Character)
{
	Super::OnPickup(Character);

	AMoneyHeistPlayerState* State = Cast<AMoneyHeistPlayerState>(Character->GetPlayerState());
	if (IsValid(State)) 
	{
		State->BombAmount += BombIncreaseAmount;
	}
}