// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "CustomSaveGame.h"
#include <Kismet/GameplayStatics.h>
#include "CheckPoint.generated.h"

UCLASS()
class CPPEXAMCLAUDIODALLAI_API ACheckPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACheckPoint();

private:
	const FString SlotName = "Slot1";
	const FName PlayerTag = "Player";

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* CheckpointTextRenderer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText CheckpointText;

	UPROPERTY(BlueprintReadOnly)
	bool bAlreadyUsed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	bool SaveGame(const FString SlotName, const int32 PlayerIndex);
	UFUNCTION()
	void OnCollisionCallback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
							 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
							 bool bFromSweep, const FHitResult& SweepResult);
};
