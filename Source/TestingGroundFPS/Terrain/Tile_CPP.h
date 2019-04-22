// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Tile_CPP.generated.h"

class UActorPool;
class UHierarchicalInstancedStaticMeshComponent;

UCLASS()
class TESTINGGROUNDFPS_API ATile_CPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile_CPP();
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void PlaceActors(TSubclassOf<AActor>ToSpawn, float Radius, int MinSpawn, int MaxSpawn, float MinScale=1, float MaxScale=1);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void PlaceGrass(UHierarchicalInstancedStaticMeshComponent *Grass, int NumToPlace);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void SetActorPool(UActorPool *PoolToSet);

private:
	bool CanSpawnAtLocation(FVector Location, float Radius);

	bool FindEmptyLocation(float Radius, FBox SpawnBoundingBox, FVector &OutSpawnPoint);

	void PlaceActor(TSubclassOf<AActor>ToSpawn, FVector SpawnPoint, float Rotation, float Scale);

	FBox GetFloorSpawnBoundingBox(UStaticMeshComponent *Floor);

	UActorComponent* GetActorFromArray(TArray<UActorComponent*> Components, FString Name);

	UStaticMeshComponent * GetFloorComponent();

	UActorPool * ActorPool;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
