// Fill out your copyright notice in the Description page of Project Settings.

#include "MoneyHeistPlayerState.h"
#include "Pickups/ScorePickup.h"

AMoneyHeistPlayerState::AMoneyHeistPlayerState()
{
    bReplicates = true;
    SetReplicates(true);
}

float AMoneyHeistPlayerState::GetWeight()
{
	return 3.0f;
}

bool AMoneyHeistPlayerState::AddItem(AScorePickup* Item)
{
    if (Items.Num() >= MaxInventorySize)
    {
        return false;
    }

    Items.Add(Item);
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

void AMoneyHeistPlayerState::UpdateWeight()
{
	//int32 Weight = GetWeight();

 //   APlayerController* LocalPlayerController = GetWorld()->GetFirstLocalPlayerFromController()->GetPlayerController(GetWorld());

 //   if (LocalPlayerController)
 //   {
 //       // Access the player state associated with the local player controller
 //       APlayerState* LocalPlayerState = LocalPlayerController->PlayerState;

 //       if (LocalPlayerState)
 //       {
 //           // Access information or perform actions related to the local player state
 //           // For example, you can get the player's score if you have a custom PlayerState class
 //           int32 PlayerScore = LocalPlayerState->GetScore();
 //       }
 //   }
}

void AMoneyHeistPlayerState::OnRep_Score()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Increase Score By %f"), Score));
    }
}

void AMoneyHeistPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AMoneyHeistPlayerState, Items);
    DOREPLIFETIME(AMoneyHeistPlayerState, MaxInventorySize);
}
