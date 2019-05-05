// Fill out your copyright notice in the Description page of Project Settings.

#include "InfiniteTerrainGameModeCPP.h"
#include "NavigationSystem/Public/NavMesh/NavMeshBoundsVolume.h"
#include "ActorPool.h"
#include "EngineUtils.h"


AInfiniteTerrainGameModeCPP::AInfiniteTerrainGameModeCPP()
{
	NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(FName("Nav Mesh Bounds Volume Pool"));
}

void AInfiniteTerrainGameModeCPP::AddtoPool(ANavMeshBoundsVolume * VolumeToAdd)
{
	NavMeshBoundsVolumePool->Add(VolumeToAdd);
}

void AInfiniteTerrainGameModeCPP::InitializeScore()
{
	score = 0;
}

void AInfiniteTerrainGameModeCPP::NewTileConquered()
{
	score = score++;
}

int AInfiniteTerrainGameModeCPP::GetScore()
{
	return score;
}

void AInfiniteTerrainGameModeCPP::SetScore(int NewScore)
{
	score = NewScore;
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
