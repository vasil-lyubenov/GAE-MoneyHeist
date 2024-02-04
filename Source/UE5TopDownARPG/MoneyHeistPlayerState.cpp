// Fill out your copyright notice in the Description page of Project Settings.

#include "MoneyHeistPlayerState.h"
#include "Pickups/ScorePickup.h"
#include "MoneyHeistMovementComponent.h"

AMoneyHeistPlayerState::AMoneyHeistPlayerState()
{
    bReplicates = true;
    SetReplicates(true);
}

float AMoneyHeistPlayerState::GetWeight() const
{
    return Weight;
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

    Items.Add(Item);
    Weight += Item->GetWeight();

    UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(GetPawn()->GetMovementComponent());
    if (MovementComponent)
    {
        MovementComponent->MaxWalkSpeed = 600.0f * FMath::Clamp(1.0f - Weight, 0.1f, 1.0f);
    }
    return true;
}

void AMoneyHeistPlayerState::RestoreInventory()
{
    // Clear inventory
    Items.Empty();

    // Update Weight to be as normal
    UpdateWeight();
}

void AMoneyHeistPlayerState::ReachedGoal()
{
    // Update Update Score
    for (int i = 0; i < Items.Num(); i++)
    {
        AScorePickup* Item = Cast<AScorePickup>(Items[i]);
        if (IsValid(Item)) 
        {
            SetScore(GetScore() + Item->GetScore());
        }
    }

    RestoreInventory();
}

AScorePickup* AMoneyHeistPlayerState::GetItemAt(int32 Position)
{
    if (Position < 0 || Position >= Items.Num())
    {
        return nullptr;
    }

    return Cast<AScorePickup>(Items[Position]);
}

void AMoneyHeistPlayerState::UpdateWeight()
{
    Weight = 0.0f;
    for (int i = 0; i < Items.Num(); i++)
    {
        Weight += GetItemAt(i)->GetWeight();
    }

    UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(GetPawn()->GetMovementComponent());
    if (MovementComponent)
    {
        MovementComponent->MaxWalkSpeed = 600.0f * FMath::Clamp(1.0f - Weight, 0.1f, 1.0f);
    }
}

void AMoneyHeistPlayerState::OnRep_Score()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Increase Score By %f"), GetScore()));
    }
}

void AMoneyHeistPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AMoneyHeistPlayerState, Items);
    DOREPLIFETIME(AMoneyHeistPlayerState, Weight);
    DOREPLIFETIME(AMoneyHeistPlayerState, MaxInventorySize);
    DOREPLIFETIME(AMoneyHeistPlayerState, bAreControlsReversed);
}
