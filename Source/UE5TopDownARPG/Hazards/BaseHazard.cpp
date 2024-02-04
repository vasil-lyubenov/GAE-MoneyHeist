// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseHazard.h"
#include "Components/BoxComponent.h"
#include "Engine/DamageEvents.h"
#include "../MoneyHeistPlayerState.h"
#include "../UE5TopDownARPGCharacter.h"


ABaseHazard::ABaseHazard()
{
	SetReplicates(true);
	bReplicates = true;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionSphereComponent"));
	BoxComponent->SetBoxExtent(FVector(100, 50, 20), true);
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	RootComponent = BoxComponent;

	BoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABaseHazard::OnBeginOverlap);
}

void ABaseHazard::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseHazard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseHazard::ActionStart(AUE5TopDownARPGCharacter* Character)
{
	AMoneyHeistPlayerState* State = Cast<AMoneyHeistPlayerState>(Character->GetPlayerState());
	if (IsValid(State) == false)
	{
		return;
	}

	State->RestoreInventory();
	if (IsValid(Character))
	{
		Character->TakeDamage(Damage, FDamageEvent(UDamageType::StaticClass()), nullptr, this);
	}
}

void ABaseHazard::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AUE5TopDownARPGCharacter* Character = Cast<AUE5TopDownARPGCharacter>(Other);
	if (IsValid(Character)) 
	{
		ActionStart(Character);
	}
}