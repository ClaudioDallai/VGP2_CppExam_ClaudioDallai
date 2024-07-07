// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPawn.h"

// Sets default values
ACustomPawn::ACustomPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitializePlayerCharacter();
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
	//PlayerInputComponent->BindAxis(FName("Look"), this, &ACustomPawn::Look)
	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ACustomPawn::Jump);

}

void ACustomPawn::InitializePlayerCharacter()
{
	// Add Skeletal Mesh
	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	SkeletalMesh->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, *SkeletalMeshPath));
	SkeletalMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// Add Animation Class
	const ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimObj(*AnimInstancePath);
	SkeletalMesh->SetAnimInstanceClass(AnimObj.Object->GeneratedClass);
}


#pragma region Inputs
void ACustomPawn::Look(FVector2D InputAxis)
{
	if (PlayerControllerInstance != nullptr)
	{
		AddControllerYawInput(InputAxis.X);
		AddControllerPitchInput(InputAxis.Y);
	}
}

void ACustomPawn::ForwardBackwardCallback(float Input)
{
	if (PlayerControllerInstance != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), Input);
	}
}

void ACustomPawn::RightLeftCallback(float Input)
{
	if (PlayerControllerInstance != nullptr)
	{
		AddMovementInput(GetActorRightVector(), Input);
	}
}

void ACustomPawn::Jump()
{
	if (PlayerControllerInstance != nullptr)
	{
		ACharacter::Jump();
	}
}

#pragma endregion

#pragma region Test Derived from Pawn
void ACustomPawn::InitializePlayerPawn()
{
	//this->SpawnCollisionHandlingMethod = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	//// Setup Capsule
	//this -> CapsuleComponentInstance = CreateAbstractDefaultSubobject<UCapsuleComponent>(TEXT("PlayerCapsule"));
	//if (CapsuleComponentInstance)
	//{
	//	CapsuleComponentInstance->SetCollisionProfileName(TEXT("Pawn"));
	//	CapsuleComponentInstance->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//}

	//this->MovementComponentInstance = CreateDefaultSubobject<UCustomMovementComponent>(TEXT("PlayerMovementComponent"));
	//this->SkeletalMeshComponentInstance = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PlayerSkeletalMesh"));

	//if (SkeletalMeshComponentInstance) 
	//{
	//	// Add Skeletal Mesh
	//	USkeletalMesh* SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, *SkeletalMeshPath);
	//	if (SkeletalMesh)
	//	{
	//		this->SkeletalMeshComponentInstance->SetSkeletalMesh(SkeletalMesh);

	//		// Add Animation Class
	//		const ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimObj(*AnimInstancePath);
	//		this->SkeletalMeshComponentInstance->SetAnimInstanceClass(AnimObj.Object->GeneratedClass);
	//	}

	//	// Skeletal Mesh Collisions
	//	SkeletalMeshComponentInstance->SetCollisionProfileName(TEXT("CharacterMesh"));
	//	SkeletalMeshComponentInstance->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	//	// Camera
	//	this->SpringArmComponentInstance = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//	this->CameraComponentInstance = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	//	this->CameraComponentInstance->SetupAttachment(SpringArmComponentInstance);

	//	// Create Hierarchy
	//	if (CapsuleComponentInstance) 
	//	{
	//		this->SkeletalMeshComponentInstance->SetupAttachment(CapsuleComponentInstance);
	//		this->SpringArmComponentInstance->SetupAttachment(CapsuleComponentInstance);
	//	}
	//}
}
#pragma endregion


