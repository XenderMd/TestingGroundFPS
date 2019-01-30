// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
//#include "/Engine/Classes/Components/MeshComponent.h"
#include "PatrolGuardCPP.generated.h"


UCLASS()
class TESTINGGROUNDFPS_API APatrolGuardCPP : public ACharacter
{
	GENERATED_BODY()


public:
	// Sets default values for this character's properties
	APatrolGuardCPP();

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector GunOffset;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	TSubclassOf <class AGunCPP>  GunBlueprint;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	//AGunCPP* Gun;
};
