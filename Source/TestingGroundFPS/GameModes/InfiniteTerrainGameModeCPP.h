// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "InfiniteTerrainGameModeCPP.generated.h"

class UActorPool;
class ANavMeshBoundsVolume;

/**
 * 
 */
UCLASS()
class TESTINGGROUNDFPS_API AInfiniteTerrainGameModeCPP : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	AInfiniteTerrainGameModeCPP();

	UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
	void PopulateBoundsVolumePool();


	UFUNCTION(BlueprintCallable, Category = "Score")
	void InitializeScore();

	UFUNCTION(BlueprintCallable, Category = "Score")
	void NewTileConquered();
	
	UFUNCTION(BlueprintCallable, Category = "Score")
	int GetScore();

	UFUNCTION(BlueprintCallable, Category = "Score")
	void SetScore(int NewScore);


private:

	void AddtoPool(ANavMeshBoundsVolume* VolumeToAdd);

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pool)
	UActorPool* NavMeshBoundsVolumePool;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Score")
	int score=0;

};
