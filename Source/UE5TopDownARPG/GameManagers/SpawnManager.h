#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMeshActor.h"
#include <Net/UnrealNetwork.h>
#include "SpawnManager.generated.h"

UCLASS()
class UE5TOPDOWNARPG_API ASpawnManager : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<AActor>> SpawnedObjectClasses;

	UPROPERTY(EditDefaultsOnly)
	float SpawnPickupDelay = 2.0f;
	
	UPROPERTY(EditDefaultsOnly)
	float SpawnVariance = 0.0f;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSoftObjectPtr<AActor>> SpawnPoints;

	// If this flag is active, then spawned can spawn even if space is taken
	UPROPERTY(EditDefaultsOnly)
	bool bCanAlwaysSpawn = false;

	// Sets default values for this actor's properties
	ASpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle CustomSpawnTickTimerHandle;

	UFUNCTION(Server, Reliable)
	void ServerRPC_RemoveObjectAt(int32 position);

	UFUNCTION(Server, Reliable)
	void ServerRPC_InitSpawnTimer();

	UFUNCTION(Server, Reliable)
	void ServerRPC_CreateObject();
public:

	// Return equal to -1 means there is not place available to spawn
	int32 GetRandomPositionToSpawn();

	// Used to stop spawning after game has ended
	UFUNCTION(Server, Reliable)
	void ServerRPC_OnGameEnd();
protected:
	TArray<AActor> SpawnedObjects;

	TSet<int32> TakenPositions;

	int32 RandomSpawnLocationIndex;

	virtual AActor* CreateObject();

	virtual void RemoveObjectAt(int32 position);
};