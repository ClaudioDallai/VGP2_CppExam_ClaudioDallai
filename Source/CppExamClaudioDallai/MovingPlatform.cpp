// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set Platform Mesh
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshPlatform"));
	PlatformMesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, *MeshPath));
	PlatformMesh->SetCollisionProfileName("BlockAllDynamic");
	PlatformMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PlatformMesh->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMovingPlatform::MoveToNextTarget()
{

}

