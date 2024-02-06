// Fill out your copyright notice in the Description page of Project Settings.


#include "UE5TopDownARPGHUD.h"
#include "UI/EndGameWidget.h"
#include "UI/StartGameWidget.h"
#include "Kismet/GameplayStatics.h"
#include "MoneyHeistPlayerState.h"

void AUE5TopDownARPGHUD::BeginPlay()
{
  Super::BeginPlay();

  APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
  if (IsValid(PlayerController))
  {
    EndGameWidget = CreateWidget<UEndGameWidget>(PlayerController, EndGameWidgetClass);
    if (IsValid(EndGameWidget))
    {
      EndGameWidget->AddToViewport();
      EndGameWidget->SetVisibility(ESlateVisibility::Collapsed);
    }

    StartGameWidget = CreateWidget<UStartGameWidget>(PlayerController, StartGameWidgetClass);
    if (IsValid(StartGameWidget))
    {
        StartGameWidget->AddToViewport();
        StartGameWidget->SetVisibility(ESlateVisibility::Collapsed);

       /* for (int i = 0; i < PlayerState->MaxInventorySize; i++)
        {

        }

        StartGameWidget->Init(PlayerController->GetPlayerState<AMoneyHeistPlayerState>());
        ShowStartGameScreen();*/
    }
  }
}

void AUE5TopDownARPGHUD::ShowEndGameScreen()
{
  if (IsValid(EndGameWidget))
  {
    EndGameWidget->SetVisibility(ESlateVisibility::Visible);
  }
}

void AUE5TopDownARPGHUD::ShowStartGameScreen()
{
    if (IsValid(StartGameWidget))
    {
        StartGameWidget->SetVisibility(ESlateVisibility::Visible);
    }
}

void AUE5TopDownARPGHUD::HideStartGameScreen()
{
    if (IsValid(StartGameWidget))
    {
        StartGameWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
}