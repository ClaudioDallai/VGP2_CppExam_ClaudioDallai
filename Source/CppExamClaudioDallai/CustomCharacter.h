// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <InputAction.h>
#include <Kismet/GameplayStatics.h>
#include "InteractionInterface.h"
#include "CustomCharacter.generated.h"

UCLASS()
class CPPEXAMCLAUDIODALLAI_API ACustomCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACustomCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	const FString SkeletalMeshPath = "/Game/Characters/Mannequins/Meshes/SKM_Quinn_Simple.SKM_Quinn_Simple";
	const FString AnimInstancePath = "/Game/Characters/Mannequins/Animations/ABP_Quinn";
	const FName PlayerTag = "Player";

public:

	#pragma region VarNotUsedAnymore
	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCapsuleComponent* CapsuleComponentInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SkeletalMeshComponentInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCustomMovementComponent* MovementComponentInstance;
	
	*/
	#pragma endregion
	
	UPROPERTY(BlueprintReadOnly)
	APlayerController* PlayerControllerInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* CameraComponentInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USpringArmComponent* SpringArmComponentInstance;

	UPROPERTY(BlueprintReadOnly)
	UCharacterMovementComponent* CharacterMovementComponentInstance;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void LookXCallback(float MouseInput);
	void LookYCallback(float MouseInput);
	void ForwardBackwardCallback(float Input);
	void RightLeftCallback(float Input);
	void Jump();
	void PlayerInteraction();
	void InteractionLineTrace(FVector StartPoint, FVector EndPoint);

private:
	void InitializePlayerPawn(); // Not Used. Still here to remember what I tryed
	void InitializePlayerCharacter();
};
