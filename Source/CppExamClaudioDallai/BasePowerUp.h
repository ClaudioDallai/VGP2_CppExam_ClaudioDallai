// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"
#include <Kismet/GameplayStatics.h>
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

	UFUNCTION()
	virtual void InteractionExecuted(AActor* Sender);
	UFUNCTION()
	virtual void PowerUpEnabled(AActor* Sender);
	UFUNCTION()
	virtual void PowerUpDisabled(AActor* Sender);
	UFUNCTION()
	virtual void PowerUpInterrupted();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Interface
	virtual bool Interaction(AActor* Sender) override;

};
