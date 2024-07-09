// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePowerUp.h"
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

protected:
	virtual void BeginPlay() override;

	// Override Interaction
	void InteractionExecuted() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Interface
	bool Interaction(AActor* Sender) override;
	
};
