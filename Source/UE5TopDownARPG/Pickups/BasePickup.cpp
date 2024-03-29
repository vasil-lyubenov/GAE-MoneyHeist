// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePickup.h"
#include "Components/SphereComponent.h"
#include "../UE5TopDownARPGCharacter.h"
#include "../UE5TopDownARPGPlayerController.h"
#include "../UE5TopDownARPG.h"

ABasePickup::ABasePickup()
{
	SetReplicates(true);
	bReplicates = true;

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphereComponent"));
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	SphereComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	RootComponent = SphereComponent;

	SphereComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABasePickup::OnBeginOverlap);
}

void ABasePickup::OnPickup(AUE5TopDownARPGCharacter* Character)
{
	OnPickupCallback.ExecuteIfBound();
}

void ABasePickup::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AUE5TopDownARPGCharacter* Character = Cast<AUE5TopDownARPGCharacter>(Other);
	if (IsValid(Character))
	{
		AUE5TopDownARPGPlayerController* Controller = Cast<AUE5TopDownARPGPlayerController>(Character->GetController());
		if (IsValid(Controller))
		{
			OnPickup(Character);
			if (bShouldGetDestroyedOnPickup) 
			{
				Destroy(true);
			}
		}
	}
}