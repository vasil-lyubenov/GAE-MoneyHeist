#include "DropOffTrigger.h"
#include "DropOffTrigger.h"
#include "../UE5TopDownARPGCharacter.h"
#include "../MoneyHeistPlayerState.h"

void ADropOffTrigger::ActionStart(AActor* ActorInRange)
{
	AUE5TopDownARPGCharacter* Character = Cast<AUE5TopDownARPGCharacter>(ActorInRange);
	if (IsValid(Character) == false) 
	{
		return;
	}

	AMoneyHeistPlayerState* State = Cast<AMoneyHeistPlayerState>(Character->GetPlayerState());
	if (IsValid(State) == false)
	{
		return;
	}

	State->ReachedGoal();
}