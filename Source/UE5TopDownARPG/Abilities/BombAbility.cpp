// Fill out your copyright notice in the Description page of Project Settings.


#include "BombAbility.h"
#include "../Projectiles/Bomb.h"
#include "../Animations/UE5TopDownARPGAnimInstance.h"
#include "GameFramework/Character.h"

bool UBombAbility::Activate(FVector Location)
{
	if (Super::Activate(Location) == false)
	{
		return false;
	}

	ServerRPC_SpawnProjectile(Location);

	return true;
}

void UBombAbility::ServerRPC_SpawnProjectile_Implementation(FVector Location)
{
	ACharacter* Owner = Cast<ACharacter>(GetOuter());
	if (IsValid(Owner) == false)
	{
		return;
	}

	FVector Direction = Location - Owner->GetActorLocation();
	Direction.Z = 0.0f;
	Direction.Normalize();

	FVector ProjectileSpawnLocation = Owner->GetActorLocation() + Direction * 100.0f;

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* Projectile = GetWorld()->SpawnActor<AActor>(BombClass, ProjectileSpawnLocation, Direction.Rotation(), SpawnParameters);
}
