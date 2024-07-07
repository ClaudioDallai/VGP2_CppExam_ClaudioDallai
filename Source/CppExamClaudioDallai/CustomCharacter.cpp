// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCharacter.h"

// Sets default values
ACustomCharacter::ACustomCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	InitializePlayerCharacter();
}

// Called when the game starts or when spawned
void ACustomCharacter::BeginPlay()
{
	Super::BeginPlay();
	this->Tags.Add(PlayerTag);
	this->PlayerControllerInstance = UGameplayStatics::GetPlayerController(GetWorld(), 0);
}

// Called every frame
void ACustomCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACustomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(FName("Forward"), this, &ACustomCharacter::ForwardBackwardCallback);
	PlayerInputComponent->BindAxis(FName("Right"), this, &ACustomCharacter::RightLeftCallback);
	PlayerInputComponent->BindAxis(FName("LookY"), this, &ACustomCharacter::LookYCallback);
	PlayerInputComponent->BindAxis(FName("LookX"), this, &ACustomCharacter::LookXCallback);
	PlayerInputComponent->BindAction(FName("Jump"), IE_Pressed, this, &ACustomCharacter::Jump);
}

void ACustomCharacter::InitializePlayerCharacter()
{
	// Add Skeletal Mesh
	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	SkeletalMesh->SetSkeletalMesh(LoadObject<USkeletalMesh>(nullptr, *SkeletalMeshPath));
	SkeletalMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	// Add Animation Class
	const ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimObj(*AnimInstancePath);
	SkeletalMesh->SetAnimInstanceClass(AnimObj.Object->GeneratedClass);
	
	// SpringArm
	SpringArmComponentInstance = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	SpringArmComponentInstance->SetupAttachment(RootComponent);
	SpringArmComponentInstance->TargetArmLength = 300.0f; 
	SpringArmComponentInstance->bUsePawnControlRotation = true;
	
	// Camera
	CameraComponentInstance = CreateAbstractDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	CameraComponentInstance->SetupAttachment(SpringArmComponentInstance, USpringArmComponent::SocketName);
	CameraComponentInstance->bUsePawnControlRotation = false;
	CameraComponentInstance->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));

	// Setup
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CharacterMovementComponentInstance = GetCharacterMovement();
	CharacterMovementComponentInstance->bOrientRotationToMovement = true;

	CharacterMovementComponentInstance->RotationRate = FRotator(0.0f, 550.0f, 0.0f);
	CharacterMovementComponentInstance->JumpZVelocity = 700.0f;
	CharacterMovementComponentInstance->AirControl = 0.45f;
	CharacterMovementComponentInstance->MaxWalkSpeed = 450.0f;
}


#pragma region Inputs
void ACustomCharacter::LookXCallback(float MouseInput)
{
	if (PlayerControllerInstance != nullptr)
	{
		AddControllerYawInput(MouseInput);
	}
}
void ACustomCharacter::LookYCallback(float MouseInput)
{
	if (PlayerControllerInstance != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f"), MouseInput);
		AddControllerPitchInput(MouseInput);
	}
}

void ACustomCharacter::ForwardBackwardCallback(float Input)
{
	if (PlayerControllerInstance != nullptr)
	{
		AddMovementInput(CameraComponentInstance->GetForwardVector(), Input);
	}
}

void ACustomCharacter::RightLeftCallback(float Input)
{
	if (PlayerControllerInstance != nullptr)
	{
		AddMovementInput(CameraComponentInstance->GetRightVector(), Input);
	}
}

void ACustomCharacter::Jump()
{
	if (PlayerControllerInstance != nullptr)
	{
		ACharacter::Jump();
	}
}

#pragma endregion


#pragma region Test Derived from Pawn
void ACustomCharacter::InitializePlayerPawn()
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


