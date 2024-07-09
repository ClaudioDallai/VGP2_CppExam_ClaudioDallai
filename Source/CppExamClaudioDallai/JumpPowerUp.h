// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePowerUp.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "JumpPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class CPPEXAMCLAUDIODALLAI_API AJumpPowerUp : public ABasePowerUp
{
	GENERATED_BODY()

public:
	AJumpPowerUp();

private:
	const FString MeshPath = "/Game/StarterContent/Props/SM_Statue.SM_Statue";
	FTimerHandle PowerUpTimerHandle;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NewJumpPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DefaultJumpPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PowerUpDuration;

protected:
	virtual void BeginPlay() override;

	// Override Interaction
	void InteractionExecuted(AActor* Sender) override;
	void PowerUpEnabled(AActor* Sender) override;
	void PowerUpDisabled(AActor* Sender) override;

	void ChangeJumpPower(AActor* Sender, float SenderJumpPower);
	void OnTimerEnd();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Interface
	bool Interaction(AActor* Sender) override;
	
};
