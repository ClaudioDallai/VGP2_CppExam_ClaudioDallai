// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include <Kismet/GameplayStatics.h>
#include "JumpPlatform.generated.h"

UCLASS()
class CPPEXAMCLAUDIODALLAI_API AJumpPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AJumpPlatform();


public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* BoxTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UArrowComponent* JumpDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LaunchForce;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void LaunchCharacterColliding(AActor* ActorColliding);

	UFUNCTION()
	void OnCollisionCallback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);
};
