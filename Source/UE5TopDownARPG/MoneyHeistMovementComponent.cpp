#include "MoneyHeistMovementComponent.h"

float UMoneyHeistMovementComponent::GetMaxSpeed() const
{
	return MySpeed * MyScale;
}

void UMoneyHeistMovementComponent::OnRep_Scale()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Scale is %f"), MyScale));
	}
}

void UMoneyHeistMovementComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMoneyHeistMovementComponent, MyScale);
	DOREPLIFETIME(UMoneyHeistMovementComponent, MySpeed);
}

bool UMoneyHeistMovementComponent::CallRemoteFunction(UFunction* Function, void* Params, FOutParmRec* OutParms, FFrame* Stack)
{
    AActor* SkillOuter = Cast<AActor>(GetOuter());
    if (IsValid(SkillOuter) == false)
    {
        return false;
    }

    UNetDriver* NetDriver = SkillOuter->GetNetDriver();
    if (IsValid(NetDriver) == false)
    {
        return false;
    }

    NetDriver->ProcessRemoteFunction(SkillOuter, Function, Params, OutParms, Stack, this);

    return true;
}

int32 UMoneyHeistMovementComponent::GetFunctionCallspace(UFunction* Function, FFrame* Stack)
{
    AActor* SkillOuter = Cast<AActor>(GetOuter());
    return (SkillOuter ? SkillOuter->GetFunctionCallspace(Function, Stack) : FunctionCallspace::Local);
}