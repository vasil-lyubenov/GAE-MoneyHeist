// Fill out your copyright notice in the Description page of Project Settings.

#include "ScorePickup.h"
#include "../UE5TopDownARPGCharacter.h"
#include "../MoneyHeistPlayerState.h"
#include "../UE5TopDownARPGPlayerController.h"

void AScorePickup::OnPickup(AUE5TopDownARPGCharacter* Character)
{
	Super::OnPickup(Character);
	AMoneyHeistPlayerState* State = Cast<AMoneyHeistPlayerState>(Character->GetPlayerState());
	if (IsValid(State) == false)
	{
		return;
	}

	if (State->AddItem(this) == false)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Inventory is Full")));
		}
	}
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