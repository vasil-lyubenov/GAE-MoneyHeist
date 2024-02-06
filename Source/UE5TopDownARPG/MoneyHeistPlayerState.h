#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include <Net/UnrealNetwork.h>
#include "MoneyHeistPlayerState.generated.h"

USTRUCT(BlueprintType)
struct UE5TOPDOWNARPG_API FPersistData {
	GENERATED_USTRUCT_BODY()

public:
	float ScoreIncrease;
	float Weight;

	FPersistData(float InitialScoreIncrease = 0, float InitialWeight = 0) : ScoreIncrease(InitialScoreIncrease), Weight(InitialWeight) {}
};

UCLASS()
class UE5TOPDOWNARPG_API AMoneyHeistPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Replicated, EditDefaultsOnly, Category = "PlayerState")
	TArray<FPersistData> Items;

	UPROPERTY(Replicated, EditDefaultsOnly, Category = "PlayerState")
	int32 MaxInventorySize = 10;

	UPROPERTY(Replicated, EditDefaultsOnly, Category = "PlayerState")
	float Weight = 0.0f;

	UPROPERTY(Replicated, EditDefaultsOnly, Category = "PlayerState")
	float CarryingScore = 0.0f;
	
	UPROPERTY(Replicated, EditDefaultsOnly, Category = "PlayerState")
	int32 BombAmount = 0;

	UPROPERTY(Replicated, EditDefaultsOnly, Category = "PlayerState")
	bool bAreControlsReversed = false;

	UPROPERTY(EditDefaultsOnly)
	float DefaultWalkingSpeed = 600.0f;

	AMoneyHeistPlayerState();

	UFUNCTION()
	float GetWeight() const;

	void OnUpdatedWeight();
	
	UFUNCTION()
	bool AreControlsReversed() const;

	UFUNCTION()
	bool AddItem(class AScorePickup* Item);

	UFUNCTION()
	void RestoreInventory();

	UFUNCTION()
	void ReachedGoal();

	UFUNCTION()
	FPersistData GetItemAt(int32 Position);

	UFUNCTION()
	void UpdateWeight();

	void UpdateScoreWidget();

	virtual void OnRep_Score() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
