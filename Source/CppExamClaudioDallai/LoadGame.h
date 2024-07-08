// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerStart.h"
#include "Components/BoxComponent.h"
#include "CustomSaveGame.h"
#include <Kismet/GameplayStatics.h>
#include "CppExamClaudioDallaiGameMode.h"
#include "LoadGame.generated.h"

UCLASS()
class CPPEXAMCLAUDIODALLAI_API ALoadGame : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALoadGame();

private:
	const FString SlotName = "Slot1";
	const FName PlayerTag = "Player";

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	APlayerStart* PlayerStartReference;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ResetPlayerToStart();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	bool LoadGameMethod(const FString SlotName, const int32 PlayerIndex);

	UFUNCTION()
	void OnCollisionCallback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
							 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
							 bool bFromSweep, const FHitResult& SweepResult);
};
