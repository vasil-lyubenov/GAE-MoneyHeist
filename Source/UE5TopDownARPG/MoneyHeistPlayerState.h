#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include <Net/UnrealNetwork.h>
#include "MoneyHeistPlayerState.generated.h"

UCLASS()
class UE5TOPDOWNARPG_API AMoneyHeistPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "PlayerState")
	TArray<AActor*> Items;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "PlayerState")
	int32 MaxInventorySize = 10;

	AMoneyHeistPlayerState();

	UFUNCTION()
	float GetWeight();

	UFUNCTION()
	bool AddItem(class AScorePickup* Item);

	UFUNCTION()
	void RestoreInventory();

	UFUNCTION()
	void ReachedGoal();

	UFUNCTION()
	void UpdateWeight();

	virtual void OnRep_Score() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
