// Fill out your copyright notice in the Description page of Project Settings.
#include "CustomActionButton.h"
#include <UE5TopDownARPG/UE5TopDownARPGHUD.h>
#include <UE5TopDownARPG/UE5TopDownARPGHUD.h>
#include "../MoneyHeistPlayerState.h"
#include "Net/UnrealNetwork.h"

UCustomActionButton::UCustomActionButton()
{
	OnClicked.AddDynamic(this, &UCustomActionButton::OnClick);
}

void UCustomActionButton::SetButtonAction(AMoneyHeistPlayerState* NewPlayerState, int32 Index)
{
	PlayerState = NewPlayerState;
	ItemIndex = Index;
}

void UCustomActionButton::OnClick()
{
	// Remove button at position
}