// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpPlatform.h"

// Sets default values
AJumpPlatform::AJumpPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LaunchForce = 2000.0f;
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("JumpTrigger"));
	JumpDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("JumpDirection"));

	JumpDirection->SetHiddenInGame(false);
	JumpDirection->SetArrowColor(FLinearColor::Red);
	JumpDirection->SetupAttachment(BoxTrigger);
}

// Called when the game starts or when spawned
void AJumpPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AJumpPlatform::OnCollisionCallback);
}

// Called every frame
void AJumpPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AJumpPlatform::LaunchCharacterColliding(AActor* ActorColliding)
{
	ACharacter* CharacterColliding = Cast<ACharacter>(ActorColliding);
	if (CharacterColliding && CharacterColliding->HasValidRootComponent())
	{
		CharacterColliding->LaunchCharacter(JumpDirection->GetForwardVector() * LaunchForce, true, true);
	}
}

void AJumpPlatform::OnCollisionCallback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		LaunchCharacterColliding(OtherActor);
	}
}

