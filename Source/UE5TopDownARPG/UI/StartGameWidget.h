#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomActionButton.h"
#include "StartGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class UE5TOPDOWNARPG_API UStartGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	TSubclassOf<class UCustomActionButton*> CustomButton;

protected:
	UPROPERTY(meta = (BindWidget))
	class UCustomActionButton* StartHostButton;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* ButtonsContainer;

	UPROPERTY(meta = (BindWidget))
	class UCustomActionButton* FindHostButton;

	/*void OnFindHostButtonPress();

	void OnStartHostButtonPress();*/

public:
	//void Init(class UCustomActionButton* CustomButton, class AMoneyHeistPlayerState* NewPlayerState);

private:
	class AMoneyHeistPlayerState* PlayerState;
};
