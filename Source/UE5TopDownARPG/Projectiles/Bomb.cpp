// Fill out your copyright notice in the Description page of Project Settings.

#include "Bomb.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Engine/DamageEvents.h"
#include "../MoneyHeistPlayerState.h"
#include "../UE5TopDownARPGCharacter.h"

ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetReplicates(true);
}

void ABomb::BeginPlay()
{
	Super::BeginPlay();
    DrawDangerZone();
	GetWorld()->GetTimerManager().SetTimer(DetonationTimerHandle, this, &ABomb::Explode, DetonationTime, false);
}

void ABomb::DrawDangerZone()
{
    DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 12, FColor::Green, false, DetonationTime, 0, 1.0f);
}

void ABomb::Explode()
{
    TArray<FHitResult> OutHits;

    // Set collision parameters
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this); // Ignore the actor initiating the sphere cast

    // Perform the sphere cast
    bool bHit = GetWorld()->SweepMultiByObjectType(
        OutHits,
        GetActorLocation(),
        GetActorLocation(),
        FQuat::Identity,
        FCollisionObjectQueryParams::AllObjects,
        FCollisionShape::MakeSphere(Radius),
        CollisionParams
    );

    if (bHit)
    {
        for (const FHitResult& HitResult : OutHits)
        {
            // Access the hit actor
            AActor* HitActor = HitResult.GetActor();

            // Your logic here based on the hit actor
            // For example, you might want to call a function on the hit actor or perform some other action
            if (IsValid(HitActor) == false)
            {
                continue;
            }

            AUE5TopDownARPGCharacter* Character = Cast<AUE5TopDownARPGCharacter>(HitActor);
            if (IsValid(Character) == false)
            {
                continue;
            }

            AMoneyHeistPlayerState* State = Cast<AMoneyHeistPlayerState>(Character->GetPlayerState());
            if (IsValid(State) == false)
            {
                continue;
            }

            State->RestoreInventory();
            if (IsValid(Character))
            {
                Character->TakeDamage(Damage, FDamageEvent(UDamageType::StaticClass()), nullptr, this);
            }
        }
    }

    Destroy(true);
}