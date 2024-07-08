// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxTrigger;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	bool SaveGame(const FString SlotName, const int32 PlayerIndex);
	UFUNCTION()
	void OnCollisionCallback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
