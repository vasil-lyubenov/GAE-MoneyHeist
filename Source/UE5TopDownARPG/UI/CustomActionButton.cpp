// Fill out your copyright notice in the Description page of Project Settings.
#include "CustomActionButton.h"
#include <UE5TopDownARPG/UE5TopDownARPGHUD.h>
#include <UE5TopDownARPG/UE5TopDownARPGHUD.h>

UCustomActionButton::UCustomActionButton()
{
	OnClicked.AddDynamic(this, &UCustomActionButton::OnClick);
}

void UCustomActionButton::OnClick()
{
	switch (ButtonActionType)
	{
		case EButtonActionType::HOST:
			OnStartHostButtonPress();
			break;
		case EButtonActionType::FIND:
			OnFindHostButtonPress();
			break;
	}
}

void UCustomActionButton::SetButtonAction(EButtonActionType ButtonAction)
{
	ButtonActionType = ButtonAction;
}

void UCustomActionButton::OnFindHostButtonPress()
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked find host action"));
	
	HideStartGameWidget();
}

void UCustomActionButton::OnStartHostButtonPress()
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked start host action"));

	HideStartGameWidget();
}

void UCustomActionButton::HideStartGameWidget()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	AUE5TopDownARPGHUD* HUD = Cast<AUE5TopDownARPGHUD>(PlayerController->GetHUD());
	if (IsValid(HUD))
	{
		HUD->HideStartGameScreen();
	}
}