// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DynamicButtonsContainerWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API UDynamicButtonsContainerWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* ButtonsContainer;

	TSubclassOf<class UButton*> CustumButtonClass;

public:
	void SetPercent(float InPercent);

	void SetText(float Score);
};
