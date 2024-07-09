// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpPowerUp.h"

AJumpPowerUp::AJumpPowerUp()
{
	PrimaryActorTick.bCanEverTick = true;
	NewJumpPower = 1200.0f;

	MeshUsedInstance = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UsedMesh"));
	MeshUsedInstance->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, *MeshPath));
	MeshUsedInstance->SetCollisionProfileName("BlockAllDynamic");
	MeshUsedInstance->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshUsedInstance->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
}

void AJumpPowerUp::BeginPlay()
{
	Super::BeginPlay();
}

void AJumpPowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AJumpPowerUp::InteractionExecuted(AActor* Sender)
{
	// Base Class Method Implementation Override
	//UE_LOG(LogTemp, Warning, TEXT("INTERFACE CALLED"));

	ACharacter* SenderCharacter = Cast<ACharacter>(Sender);
	if (SenderCharacter)
	{
		UCharacterMovementComponent* MovementComponent =  SenderCharacter->GetCharacterMovement();
		if (MovementComponent)
		{
			MovementComponent->JumpZVelocity = NewJumpPower;
		}
	}
}

bool AJumpPowerUp::Interaction(AActor* Sender)
{
	if (Sender)
	{
		InteractionExecuted(Sender);
		return true;
	}

	return false;
}
