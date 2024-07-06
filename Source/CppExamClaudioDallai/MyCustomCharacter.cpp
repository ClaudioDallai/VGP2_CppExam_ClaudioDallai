// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCustomCharacter.h"

// Sets default values
AMyCustomCharacter::AMyCustomCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCustomCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCustomCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCustomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

