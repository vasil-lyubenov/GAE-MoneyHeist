// Fill out your copyright notice in the Description page of Project Settings.

#include "ScorePickup.h"
#include "../UE5TopDownARPGCharacter.h"
#include "../MoneyHeistPlayerState.h"

void AScorePickup::OnPickup(AUE5TopDownARPGCharacter* Character)
{
	Super::OnPickup(Character);
	//Character->ServerRPC_UpdateState(this);

	AMoneyHeistPlayerState* State = Cast<AMoneyHeistPlayerState>(Character->GetPlayerState());
	if (IsValid(State) == false)
	{
		return;
	}

	if (State->AddItem(this))
	{
		//Weight += Pickup->GetWeight();
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