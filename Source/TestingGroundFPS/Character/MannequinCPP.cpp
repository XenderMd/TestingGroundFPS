// Fill out your copyright notice in the Description page of Project Settings.

#include "MannequinCPP.h"
#include "Weapons/Projectile.h"
#include "Weapons/GunCPP.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId


// Sets default values
AMannequinCPP::AMannequinCPP()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);

	
}

// Called when the game starts or when spawned
void AMannequinCPP::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(GunBlueprint)) { return; }
	Gun = GetWorld()->SpawnActor<AGunCPP>(GunBlueprint);

	if (IsPlayerControlled())
	{
		//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
		Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint_FP"));
	}
	else
	{
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint_TP"));
	}

	Gun->FPAnimInstance = Mesh1P->GetAnimInstance();
	Gun->TPAnimInstance = GetMesh()->GetAnimInstance();
	
}


// Called every frame
void AMannequinCPP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMannequinCPP::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//Bind the FireInput component
	if (PlayerInputComponent != NULL)
	{InputComponent->BindAction("Fire", IE_Pressed, this, &AMannequinCPP::PullTrigger);}

}

void AMannequinCPP::UnPossessed()
{
	Super::UnPossessed();

	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint_TP"));

}

void AMannequinCPP::PullTrigger()
{
	Gun->OnFire();
}

