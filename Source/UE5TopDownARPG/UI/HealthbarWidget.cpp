// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthbarWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHealthbarWidget::SetPercent(float InPercent)
{
	float Percent = FMath::Max(FMath::Min(InPercent, 1.0f), 0.f);
	HealthProgressBar->SetPercent(Percent);
}

void UHealthbarWidget::SetText(float Score)
{
	FString NewText = FString::Printf(TEXT("Score: %.2f"), Score); // Format the float to a string with 2 decimal places
	ScoreText->SetText(FText::FromString(NewText));
}