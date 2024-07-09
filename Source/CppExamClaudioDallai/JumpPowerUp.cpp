// Fill out your copyright notice in the Description page of Project Settings.


#include "JumpPowerUp.h"

AJumpPowerUp::AJumpPowerUp()
{
	PrimaryActorTick.bCanEverTick = true;

	NewJumpPower = 1200.0f;
	DefaultJumpPower = 600.0f;
	PowerUpDuration = 5.0f;

	MeshUsedInstance = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UsedMesh"));
	MeshUsedInstance->SetStaticMesh(LoadObject<UStaticMesh>(nullptr, *MeshPath));
	MeshUsedInstance->SetCollisionProfileName("BlockAllDynamic");
	MeshUsedInstance->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshUsedInstance->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
}

void AJumpPowerUp::BeginPlay()
{
	Super::BeginPlay();

	ACppExamClaudioDallaiGameMode* CurrentGameMode = Cast<ACppExamClaudioDallaiGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (CurrentGameMode)
	{
		CurrentGameMode->OnPlayerFellOff.AddDynamic(this, &AJumpPowerUp::PowerUpInterrupted);
	}
}

void AJumpPowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

#pragma region Base Methods Override

void AJumpPowerUp::InteractionExecuted(AActor* Sender)
{
	// Base Class Method Implementation Override
	//UE_LOG(LogTemp, Warning, TEXT("INTERFACE CALLED"));

	PowerUpEnabled(Sender);
	GetWorld()->GetTimerManager().ClearTimer(PowerUpTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(PowerUpTimerHandle, this, &AJumpPowerUp::OnTimerEnd, PowerUpDuration, false);
}

void AJumpPowerUp::PowerUpEnabled(AActor* Sender)
{
	if (Sender)
	{
		ChangeJumpPower(Sender, NewJumpPower);
	}
}

void AJumpPowerUp::PowerUpDisabled(AActor* Sender)
{
	if (Sender)
	{
		ChangeJumpPower(Sender, DefaultJumpPower);
	}
}

void AJumpPowerUp::PowerUpInterrupted()
{
	//UE_LOG(LogTemp, Warning, TEXT("DYNAMIC MULTICAST DELEGATE CALLED"));
	if (PowerUpTimerHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(PowerUpTimerHandle);
		if (LastActorInteractedWith)
		{
			PowerUpDisabled(LastActorInteractedWith);
		}
	}
}

#pragma endregion

void AJumpPowerUp::ChangeJumpPower(AActor* Sender, float SenderJumpPower)
{
	ACharacter* SenderCharacter = Cast<ACharacter>(Sender);
	if (SenderCharacter)
	{
		UCharacterMovementComponent* MovementComponent = SenderCharacter->GetCharacterMovement();
		if (MovementComponent)
		{
			MovementComponent->JumpZVelocity = SenderJumpPower;
		}
	}
}

void AJumpPowerUp::OnTimerEnd()
{
	PowerUpDisabled(LastActorInteractedWith);
}

// Interface
bool AJumpPowerUp::Interaction(AActor* Sender)
{
	if (Sender)
	{
		LastActorInteractedWith = Sender;
		InteractionExecuted(Sender);
		return true;
	}

	return false;
}
