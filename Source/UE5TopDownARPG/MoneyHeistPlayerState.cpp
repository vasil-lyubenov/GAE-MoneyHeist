// Fill out your copyright notice in the Description page of Project Settings.

#include "MoneyHeistPlayerState.h"
#include "Pickups/ScorePickup.h"
#include "MoneyHeistMovementComponent.h"
#include "UE5TopDownARPGCharacter.h"
#include "UE5TopDownARPGPlayerController.h"

AMoneyHeistPlayerState::AMoneyHeistPlayerState()
{
    bReplicates = true;
    SetReplicates(true);
}

float AMoneyHeistPlayerState::GetWeight() const
{
    return Weight;
}

void AMoneyHeistPlayerState::OnUpdatedWeight()
{
    AUE5TopDownARPGCharacter* Character = Cast<AUE5TopDownARPGCharacter>(GetPawn());
    if (IsValid(Character->GetController()))
	{
		AUE5TopDownARPGPlayerController* TopDownController = Cast<AUE5TopDownARPGPlayerController>(Character->GetController());

		TopDownController->AdjustSpeedByState();
	}
    return;
}

bool AMoneyHeistPlayerState::AreControlsReversed() const
{
    return bAreControlsReversed;
}

bool AMoneyHeistPlayerState::AddItem(AScorePickup* Item)
{
    if (Items.Num() >= MaxInventorySize)
    {
        return false;
    }

    Weight += Item->GetWeight();
    CarryingScore += Item->GetScore();
    Items.Add(FPersistData(Item->GetScore(), Item->GetWeight()));
    OnUpdatedWeight();

    return true;
}

void AMoneyHeistPlayerState::RestoreInventory()
{
    // Clear inventory
    Items.Empty();

    // Update Weight to be as normal
    UpdateWeight();

    CarryingScore = 0.0f;
}

void AMoneyHeistPlayerState::ReachedGoal()
{
    // Update Score
    SetScore(GetScore() + CarryingScore);
    OnRep_Score();
    RestoreInventory();
}

FPersistData AMoneyHeistPlayerState::GetItemAt(int32 Position)
{
    if (Position < 0 || Position >= Items.Num())
    {
        return FPersistData(0, 0);
    }

    return Items[Position];
}

void AMoneyHeistPlayerState::UpdateWeight()
{
    Weight = 0.0f;
    for (int i = 0; i < Items.Num(); i++)
    {
        Weight += GetItemAt(i).Weight;
    }
    OnUpdatedWeight();
}

void AMoneyHeistPlayerState::UpdateScoreWidget()
{
    AUE5TopDownARPGCharacter* Character = Cast<AUE5TopDownARPGCharacter>(GetPawn());
    if (IsValid(Character) == false)
    {
        return;
    }
    Character->SetScore(Score);
}

void AMoneyHeistPlayerState::OnRep_Score()
{
    UpdateScoreWidget();
}

void AMoneyHeistPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AMoneyHeistPlayerState, Items);
    DOREPLIFETIME(AMoneyHeistPlayerState, Weight);
    DOREPLIFETIME(AMoneyHeistPlayerState, MaxInventorySize);
    DOREPLIFETIME(AMoneyHeistPlayerState, bAreControlsReversed);
    DOREPLIFETIME(AMoneyHeistPlayerState, BombAmount);
}
