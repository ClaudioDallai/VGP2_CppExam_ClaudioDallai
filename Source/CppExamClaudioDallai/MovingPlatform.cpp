// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Index = 0;
	SetCurrentStartTransform();

	// Set Platform Mesh
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshPlatform"));
	PlatformMesh->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, *MeshPath));
	PlatformMesh->SetCollisionProfileName("BlockAllDynamic");
	PlatformMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	PlatformMesh->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));

	// TimeLine
	CustomTimelineInstance = CreateDefaultSubobject<UTimelineComponent>(TEXT("PlatformTimeline"));
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	// TimeLine
	FOnTimelineFloat TimelineCallback;
	FOnTimelineEvent TimelineFinishedCallback;

	TimelineCallback.BindUFunction(this, FName("HandleProgress"));
	TimelineFinishedCallback.BindUFunction(this, FName("HandleFinish"));

	CustomTimelineInstance->AddInterpFloat(TimeLineFloatCurve, TimelineCallback);
	CustomTimelineInstance->SetTimelineFinishedFunc(TimelineFinishedCallback);

	CustomTimelineInstance->SetLooping(false);
	CustomTimelineInstance->SetIgnoreTimeDilation(true);

	if (!TransformArray.IsEmpty())
	{
		CustomTimelineInstance->PlayFromStart();
	}
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMovingPlatform::MoveToNextTarget()
{
	CurrentTransformTarget = TransformArray[Index];
}

void AMovingPlatform::HandleFinish()
{
	Index = (Index + 1) % TransformArray.Num();
	MoveToNextTarget();
	SetCurrentStartTransform();
	CustomTimelineInstance->PlayFromStart();
}

void AMovingPlatform::HandleProgress(float Alpha)
{
	UE_LOG(LogTemp, Warning, TEXT("%f"), Alpha);
	if (CustomTimelineInstance->IsPlaying())
	{
		FTransform Transform;
		Transform.LerpTranslationScale3D(StartTransformTarget, CurrentTransformTarget, ScalarRegister(Alpha));
		this->SetActorTransform(Transform);
	}
}

void AMovingPlatform::SetCurrentStartTransform()
{
	StartTransformTarget = this->GetActorTransform();
}

