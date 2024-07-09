// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"
#include "BasePowerUp.generated.h"

UCLASS()
class CPPEXAMCLAUDIODALLAI_API ABasePowerUp : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePowerUp();

protected:
	AActor* LastActorInteractedWith;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshUsedInstance;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void InteractionExecuted(AActor* Sender);
	virtual void PowerUpEnabled(AActor* Sender);
	virtual void PowerUpDisabled(AActor* Sender);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Interface
	virtual bool Interaction(AActor* Sender) override;

};
