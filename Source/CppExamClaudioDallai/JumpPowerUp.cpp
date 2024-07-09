// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpPowerUp.h"

AJumpPowerUp::AJumpPowerUp()
{
	PrimaryActorTick.bCanEverTick = true;

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

void AJumpPowerUp::InteractionExecuted()
{
	// Base Class Method Implementation Override
	UE_LOG(LogTemp, Warning, TEXT("INTERFACE CALLED"));
}

bool AJumpPowerUp::Interaction(AActor* Sender)
{
	InteractionExecuted();
	return true;
}
