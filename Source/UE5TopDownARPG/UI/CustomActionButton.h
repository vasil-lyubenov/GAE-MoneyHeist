// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "CustomActionButton.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FClickDelegate);

UENUM()
enum EButtonActionType
{
	NONE,
	FIND,
	HOST
};


UCLASS()
class UE5TOPDOWNARPG_API UCustomActionButton : public UButton
{
	GENERATED_BODY()
protected:
	EButtonActionType ButtonActionType;

public:
	UCustomActionButton();

	UPROPERTY()
	FClickDelegate click;

	UFUNCTION()
	void SetButtonAction(EButtonActionType ButtonActionType);

	UFUNCTION()
	void OnClick();

	UFUNCTION()
	void OnFindHostButtonPress();

	UFUNCTION()
	void OnStartHostButtonPress();

	UFUNCTION()
	void HideStartGameWidget();
};