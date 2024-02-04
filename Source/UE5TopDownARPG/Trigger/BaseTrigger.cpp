// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTrigger.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "../UE5TopDownARPG.h"
#include "../UE5TopDownARPGCharacter.h"

// Sets default values
ABaseTrigger::ABaseTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionSphereComponent"));
	BoxComponent->SetBoxExtent(FVector(100, 50, 20), true);
	BoxComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	RootComponent = BoxComponent;

	BoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &ABaseTrigger::OnBeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &ABaseTrigger::OnEndOverlap);
}

// Called when the game starts or when spawned
void ABaseTrigger::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseTrigger::ActionStart(AActor* ActorInRange)
{

}

void ABaseTrigger::ActionEnd(AActor* ActorInRange)
{

}

void ABaseTrigger::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("OverlapBegin %s %s"), *Other->GetName(), *OtherComp->GetName());
	ActionStart(Other);
}

void ABaseTrigger::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogUE5TopDownARPG, Log, TEXT("OverlapEnd %s %s"), *Other->GetName(), *OtherComp->GetName());
	ActionEnd(Other);
}

// Called every frame
void ABaseTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

