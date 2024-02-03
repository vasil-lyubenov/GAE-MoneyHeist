#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Net/UnrealNetwork.h>
#include "MoneyHeistMovementComponent.generated.h"

UCLASS()
class UE5TOPDOWNARPG_API UMoneyHeistMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	virtual bool IsSupportedForNetworking() const override { return true; }
	virtual bool CallRemoteFunction(UFunction* Function, void* Params, struct FOutParmRec* OutParms, FFrame* Stack) override;
	virtual int32 GetFunctionCallspace(UFunction* Fuction, FFrame* Stack) override;

	UPROPERTY(Replicated)
	float MySpeed = 600.0f;

	UPROPERTY(ReplicatedUsing = OnRep_Scale)
	float MyScale = 1.0f;
	
	float GetMaxSpeed() const override;

	UFUNCTION()
	void OnRep_Scale();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
