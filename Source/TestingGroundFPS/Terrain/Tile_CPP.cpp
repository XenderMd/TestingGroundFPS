// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile_CPP.h"


// Sets default values
ATile_CPP::ATile_CPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ATile_CPP::PlaceActors(TSubclassOf<AActor>ToSpawn, int MinSpawn, int MaxSpawn)
{

	FBox SpawnBoundingBox;
	FBoxSphereBounds FloorBounds;
	FVector FloorCenter;
	FVector FloorExtent;
	FVector Min;
	FVector Max;
	

	UStaticMeshComponent *Floor;

	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	
	//Get a reference to the Tile floor component
	Floor = Cast<UStaticMeshComponent>(FindComponentByClass<UStaticMeshComponent>());

	//Check for null pointer
	if (Floor != nullptr)
	{
		//Get the bounding box for the floor component in World coordinates
		Floor->GetBodySetup()->AggGeom.CalcBoxSphereBounds(FloorBounds, FTransform(Floor->GetComponentToWorld()));
		//Get floor parameters - for the center, again World Cooridinates
		FloorCenter = FloorBounds.GetBox().GetCenter();
		FloorExtent = FloorBounds.GetBox().GetExtent();
		
		//Calculate Min and Max based on the floor center and the floor extent  -> these will be again in World coordinates
		//Since we want a "flat" spawning box, use the "Z" component of the extent vector to compensate for the center displacement on the Z axis
		Min = FloorCenter - FVector(FloorExtent.X, FloorExtent.Y, -(FloorExtent.Z));
		Max = FloorCenter + FVector(FloorExtent.X, FloorExtent.Y, FloorExtent.Z);
		//Generate the spawn bounding box
		SpawnBoundingBox = FBox(Min, Max);

		//Spawn objects
		for (size_t i = 0; i < NumberToSpawn; i++)
		{
			FVector SpawnPoint = FMath::RandPointInBox(SpawnBoundingBox);
			AActor *Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn, SpawnPoint, GetActorRotation());
			// Since we used World coordinates -> EAttachmentRule::KeepWorld
			Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));
		}
	}

}

// Called when the game starts or when spawned
void ATile_CPP::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile_CPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

