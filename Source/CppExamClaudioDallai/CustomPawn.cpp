// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPawn.h"

// Sets default values
ACustomPawn::ACustomPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitializePlayerPawn();
}

// Called when the game starts or when spawned
void ACustomPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACustomPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACustomPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACustomPawn::InitializePlayerPawn()
{
	// Setup Capsule
	this -> CapsuleComponentInstance = CreateAbstractDefaultSubobject<UCapsuleComponent>(TEXT("PlayerCapsule"));
	if (CapsuleComponentInstance)
	{
		CapsuleComponentInstance->SetCollisionProfileName(TEXT("Pawn"));
		CapsuleComponentInstance->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}

	this->MovementComponentInstance = CreateDefaultSubobject<UCustomMovementComponent>(TEXT("PlayerMovementComponent"));
	this->SkeletalMeshComponentInstance = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerSkeletalMesh"));

	if (SkeletalMeshComponentInstance) 
	{
		// Add Skeletal Mesh
		USkeletalMesh* SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, *SkeletalMeshPath);
		if (SkeletalMesh)
		{
			this->SkeletalMeshComponentInstance->SetSkeletalMesh(SkeletalMesh);

			// Add Animation Class
			const ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimObj(*AnimInstancePath);
			this->SkeletalMeshComponentInstance->SetAnimInstanceClass(AnimObj.Object->GeneratedClass);
		}

		// Skeletal Mesh Collisions
		SkeletalMeshComponentInstance->SetCollisionProfileName(TEXT("CharacterMesh"));
		SkeletalMeshComponentInstance->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

		// Camera
		this->SpringArmComponentInstance = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
		this->CameraComponentInstance = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
		this->CameraComponentInstance->SetupAttachment(SpringArmComponentInstance);

		// Create Hierarchy
		if (CapsuleComponentInstance) 
		{
			this->SkeletalMeshComponentInstance->SetupAttachment(CapsuleComponentInstance);
			this->SpringArmComponentInstance->SetupAttachment(CapsuleComponentInstance);
		}
	}
}

