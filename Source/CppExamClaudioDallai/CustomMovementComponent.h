// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CustomMovementComponent.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class CPPEXAMCLAUDIODALLAI_API UCustomMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
public:
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* TickFunction) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsGrounded;
	bool bCannotMoveForward = false;
	bool bCannotMoveBackward = false;

	UFUNCTION(BlueprintCallable)
	void MoveForward(float Input);
	UFUNCTION(BlueprintCallable)
	void MoveRight(float Input);
	void CustomJump();
};
