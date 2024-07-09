// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/SaveGame.h"
#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GameplayStatics.h"
#include "WinTrigger.generated.h"

UCLASS()
class CPPEXAMCLAUDIODALLAI_API AWinTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWinTrigger();

private:
	const FString SlotName = "Slot1";
	const FName PlayerTag = "Player";

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* WinTextRenderer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText WinText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName LevelToOpen = "/Game/Custom/Levels/L_MainMap.L_MainMap";

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void RestartLevelAfterWin();
	UFUNCTION()
	void DeleteCurrentSaveSlot(const FString Slot, const int32 PlayerIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnCollisionCallback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	
};
