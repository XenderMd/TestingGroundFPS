// Fill out your copyright notice in the Description page of Project Settings.

#include "Tile_CPP.h"
#include "DrawDebugHelpers.h"


// Sets default values
ATile_CPP::ATile_CPP()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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



void ATile_CPP::PlaceActors(TSubclassOf<AActor>ToSpawn, float Radius, int MinSpawn, int MaxSpawn)
{

	
	FBox SpawnBoundingBox;
	FVector SpawnPoint;
	UStaticMeshComponent *Floor;
	int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
	
	//Get a reference to the Tile floor component
	Floor = Cast<UStaticMeshComponent>(FindComponentByClass<UStaticMeshComponent>());

	//Check for null pointer
	if (Floor != nullptr)
	{
		SpawnBoundingBox = GetFloorSpawnBoundingBox(Floor);

		//Spawn objects
		for (size_t i = 0; i < NumberToSpawn; i++)
		{
			if (FindEmptyLocation(Radius, SpawnBoundingBox, SpawnPoint))
			{
				PlaceActor(ToSpawn, SpawnPoint);
			}
		}
	}

}

bool ATile_CPP::FindEmptyLocation(float Radius, FBox SpawnBoundingBox, FVector &OutSpawnPoint)
{
	FVector CandidatePoint;
	const int MaxAttempts=100;
	bool isFound = false;

	for (int i = 0; i < MaxAttempts&&!isFound; i++)
	{
		CandidatePoint = FMath::RandPointInBox(SpawnBoundingBox);
		isFound=CanSpawnAtLocation(CandidatePoint, Radius);
	}


	if (isFound) {OutSpawnPoint = CandidatePoint;}
	return isFound;
}

void ATile_CPP::PlaceActor(TSubclassOf<AActor> ToSpawn, FVector SpawnPoint)
{

	AActor *Spawned = GetWorld()->SpawnActor<AActor>(ToSpawn, SpawnPoint, GetActorRotation());
	// Since we used World coordinates -> EAttachmentRule::KeepWorld
	Spawned->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepWorld, false));

}

FBox ATile_CPP::GetFloorSpawnBoundingBox(UStaticMeshComponent * Floor)
{
	FBoxSphereBounds FloorBounds;
	FBox SpawnBoundingBox;
	FVector FloorCenter;
	FVector FloorExtent;
	FVector Min;
	FVector Max;
	
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

	return SpawnBoundingBox;
}

bool ATile_CPP::CanSpawnAtLocation(FVector Location, float Radius)
{
	FHitResult HitResult;
	bool HasHit=GetWorld()->SweepSingleByChannel(
		HitResult,
		Location,
		Location,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(Radius));

	FColor ResultColor = HasHit ? FColor::Red: FColor::Green;
	DrawDebugCapsule(GetWorld(), Location, 0, Radius, FQuat::Identity, ResultColor, true, 100);

	return !HasHit;
}
