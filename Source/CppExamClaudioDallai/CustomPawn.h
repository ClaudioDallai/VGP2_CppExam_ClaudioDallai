// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SkeletalMeshComponent.h"
#include "CustomMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include <Kismet/GameplayStatics.h>
#include "CustomPawn.generated.h"

UCLASS()
class CPPEXAMCLAUDIODALLAI_API ACustomPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACustomPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	const FString SkeletalMeshPath = "/Game/Characters/Mannequins/Meshes/SKM_Quinn_Simple.SKM_Quinn_Simple";
	const FString AnimInstancePath = "/Game/Custom/ABP_CustomManny.ABP_CustomManny";

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComponentInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMeshComponentInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCustomMovementComponent* MovementComponentInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComponentInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArmComponentInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APlayerController* PlayerControllerInstance;
	


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Look(FVector2D InputAxis);
	void ForwardBackwardCallback(float Input);
	void RightLeftCallback(float Input);
	void Jump();

private:
	void InitializePlayerPawn();
};
