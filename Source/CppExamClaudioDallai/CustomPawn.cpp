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
	this->PlayerControllerInstance = UGameplayStatics::GetPlayerController(GetWorld(), 0);
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
	PlayerInputComponent->BindAxis(FName("Forward"), this, &ACustomPawn::ForwardBackwardCallback);
	PlayerInputComponent->BindAxis(FName("Right"), this, &ACustomPawn::RightLeftCallback);
	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ACustomPawn::Jump);

}

void ACustomPawn::InitializePlayerPawn()
{
	this->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

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


#pragma region Inputs
void ACustomPawn::Look(FVector2D InputAxis)
{
	if (Controller != nullptr)
	{
		AddControllerYawInput(InputAxis.X);
		AddControllerPitchInput(InputAxis.Y);
	}
}

void ACustomPawn::ForwardBackwardCallback(float Input)
{
	this->MovementComponentInstance->MoveForward(Input);
}

void ACustomPawn::RightLeftCallback(float Input)
{
	this->MovementComponentInstance->MoveRight(Input);
}

void ACustomPawn::Jump()
{
	this->MovementComponentInstance->CustomJump();
}

#pragma endregion
