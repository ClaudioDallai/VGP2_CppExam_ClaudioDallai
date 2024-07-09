// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePowerUp.h"

// Sets default values
ABasePowerUp::ABasePowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshUsedInstance = nullptr;
}

// Called when the game starts or when spawned
void ABasePowerUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePowerUp::InteractionExecuted(AActor* Sender)
{
	// Base Class Method
}

bool ABasePowerUp::Interaction(AActor* Sender)
{
	// Base Interface Method
	return false;
}

