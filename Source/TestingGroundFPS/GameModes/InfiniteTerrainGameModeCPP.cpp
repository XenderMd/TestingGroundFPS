// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameModeCPP.h"
#include "NavigationSystem/Public/NavMesh/NavMeshBoundsVolume.h"
#include "EngineUtils.h"


void AInfiniteTerrainGameModeCPP::AddtoPool(ANavMeshBoundsVolume * VolumeToAdd)
{
	UE_LOG(LogTemp, Warning, TEXT("NaveMesh name is: %s"), *VolumeToAdd->GetName());
}


void AInfiniteTerrainGameModeCPP::PopulateBoundsVolumePool()
{
	TActorIterator<ANavMeshBoundsVolume> VolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());
	while (VolumeIterator)
	{
	   AddtoPool(*VolumeIterator);
	   ++VolumeIterator;
	}
}
