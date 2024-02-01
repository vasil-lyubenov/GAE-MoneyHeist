// Fill out your copyright notice in the Description page of Project Settings.

#include "StartGameWidget.h"
#include "Components/Button.h"

void UStartGameWidget::OnFindHostButtonPress()
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked find host action"));
}

void UStartGameWidget::OnStartHostButtonPress()
{
	UE_LOG(LogTemp, Warning, TEXT("Clicked start host action"));
}

void UStartGameWidget::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Added find host action"));
	FindHostButton->SetButtonAction(EButtonActionType::FIND);

	UE_LOG(LogTemp, Warning, TEXT("Added start host action"));
	StartHostButton->SetButtonAction(EButtonActionType::HOST);
}