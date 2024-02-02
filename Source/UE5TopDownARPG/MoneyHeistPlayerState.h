// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MoneyHeistPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API AMoneyHeistPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "PlayerState")
	TArray<float> Items;

	UFUNCTION()
	float GetWeight();

	UFUNCTION()
	bool AddItem(float Item);

	UFUNCTION()
	void RestoreInventory();

	UFUNCTION()
	void ReachedGoal();

	UFUNCTION()
	void UpdateWeight();

	virtual void OnRep_Score() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
