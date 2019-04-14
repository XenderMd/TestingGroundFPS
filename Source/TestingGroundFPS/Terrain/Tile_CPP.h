// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Tile_CPP.generated.h"

UCLASS()
class TESTINGGROUNDFPS_API ATile_CPP : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile_CPP();
	
	UFUNCTION(BlueprintCallable, Category = "Setup")
	void PlaceActors(TSubclassOf<AActor>ToSpawn, float Radius, int MinSpawn, int MaxSpawn);

private:
	bool CanSpawnAtLocation(FVector Location, float Radius);

	bool FindEmptyLocation(float Radius, FBox SpawnBoundingBox, FVector &OutSpawnPoint);

	void PlaceActor(TSubclassOf<AActor>ToSpawn, FVector SpawnPoint);

	FBox GetFloorSpawnBoundingBox(UStaticMeshComponent *Floor);



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	
	
};
