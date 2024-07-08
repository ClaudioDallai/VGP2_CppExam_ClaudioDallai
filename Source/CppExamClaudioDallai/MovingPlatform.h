// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "MovingPlatform.generated.h"

UCLASS()
class CPPEXAMCLAUDIODALLAI_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

private:
	const FString MeshPath = "/Game/StarterContent/Shapes/Shape_Plane.Shape_Plane";
	int32 Index;
	FTransform CurrentTransformTarget;
	FTransform StartTransformTarget;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTransform> TransformArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTimelineComponent* CustomTimelineInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* TimeLineFloatCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DelayTime;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void ManageNextTarget();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void MoveToNextTarget();
	UFUNCTION()
	void HandleFinish();
	UFUNCTION()
	void HandleProgress(float Alpha);
	UFUNCTION()
	void SetCurrentStartTransform();
};
