// Fill out your copyright notice in the Description page of Project Settings.

#include "PatrolGuardCPP.h"
#include "Weapons/GunCPP.h"
#include "Weapons/Projectile.h"


// Sets default values
APatrolGuardCPP::APatrolGuardCPP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APatrolGuardCPP::BeginPlay()
{
	Super::BeginPlay();
	//FP_Gun->AttachToComponent(Mesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	if (!ensure(GunBlueprint)) { return; }
	Gun = GetWorld()->SpawnActor<AGunCPP>(GunBlueprint);

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	Gun->AttachToComponent((this->GetMesh()), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	Gun->AnimInstance = (this->GetMesh())->GetAnimInstance();
	
}

// Called every frame
void APatrolGuardCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APatrolGuardCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

