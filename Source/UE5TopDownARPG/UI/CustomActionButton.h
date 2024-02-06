// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "CustomActionButton.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FClickDelegate);

UCLASS()
class UE5TOPDOWNARPG_API UCustomActionButton : public UButton
{
	GENERATED_BODY()

public:

	class AMoneyHeistPlayerState* PlayerState;

	int32 ItemIndex;

	UCustomActionButton();

	UPROPERTY()
	FClickDelegate click;

	UFUNCTION()
	void SetButtonAction(class AMoneyHeistPlayerState* NewPlayerState, int32 Index);

	UFUNCTION()
	void OnClick();
};