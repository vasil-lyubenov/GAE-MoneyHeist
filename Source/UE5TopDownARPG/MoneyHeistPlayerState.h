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

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "PlayerState")
	float Weight = 0.0f;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "PlayerState")
	float CarryingScore = 0.0f;
	
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "PlayerState")
	int32 BombAmount = 0;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "PlayerState")
	bool bAreControlsReversed = false;

	UPROPERTY(EditDefaultsOnly)
	float DefaultWalkingSpeed = 600.0f;

	AMoneyHeistPlayerState();

	UFUNCTION()
	float GetWeight() const;
	
	UFUNCTION()
	bool AreControlsReversed() const;

	UFUNCTION()
	bool AddItem(class AScorePickup* Item);

	UFUNCTION()
	void RestoreInventory();

	UFUNCTION()
	void ReachedGoal();

	UFUNCTION()
	AScorePickup* GetItemAt(int32 Position);

	UFUNCTION()
	void UpdateWeight();

	void UpdateScoreWidget();

	virtual void OnRep_Score() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
