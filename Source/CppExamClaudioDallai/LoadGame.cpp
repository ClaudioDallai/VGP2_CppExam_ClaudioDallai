// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadGame.h"

// Sets default values
ALoadGame::ALoadGame()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerStartReference = nullptr;
	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("LoadBoxTrigger"));
}

// Called when the game starts or when spawned
void ALoadGame::BeginPlay()
{
	Super::BeginPlay();
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ALoadGame::OnCollisionCallback);

	ACppExamClaudioDallaiGameMode* CurrentGamemode = Cast<ACppExamClaudioDallaiGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (CurrentGamemode)
	{
		if (UGameplayStatics::DoesSaveGameExist(SlotName, 0) && !CurrentGamemode->GetIsLoaded())
		{
			CurrentGamemode->SetIsLoaded(true);
			LoadGameMethod(SlotName, 0);
		}
	}
}

void ALoadGame::ResetPlayerToStart()
{
	UWorld* CurrentWorld = GetWorld();
	if (!CurrentWorld)
	{
		return;
	}

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(CurrentWorld, 0);
	if (!PlayerPawn)
	{
		return;
	}

	if (PlayerStartReference)
	{
		PlayerPawn->SetActorLocation(PlayerStartReference->GetActorLocation());
		PlayerPawn->SetActorRotation(PlayerStartReference->GetActorRotation());
	}

	AController* PlayerController = UGameplayStatics::GetPlayerController(CurrentWorld, 0);
	if (!PlayerController)
	{
		return;
	}

	PlayerController->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
}

// Called every frame
void ALoadGame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ALoadGame::LoadGameMethod(const FString Slot, const int32 PlayerIndex)
{
	UCustomSaveGame* LoadGame = Cast<UCustomSaveGame>(UGameplayStatics::LoadGameFromSlot(Slot, PlayerIndex));
	if (LoadGame)
	{
		UWorld* CurrentWorld = GetWorld();
		if (!CurrentWorld)
		{
			return false;
		}

		APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(CurrentWorld, 0);
		if (!PlayerPawn)
		{
			return false;
		}

		// Load Datas
		PlayerPawn->SetActorTransform(LoadGame->PlayerDataStruct.PlayerTransform);
		ACharacter* Character = Cast<ACharacter>(PlayerPawn);
		if (Character)
		{
			UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
			if (MovementComponent)
			{
				MovementComponent->JumpZVelocity = LoadGame->PlayerDataStruct.PlayerJumpZForce;
			}
		}

		return true;
	}

	return false;
}

void ALoadGame::OnCollisionCallback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag(PlayerTag))
	{
		if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
		{
			LoadGameMethod(SlotName, 0);
		}
		else
		{
			ResetPlayerToStart();
		}

		NotifyPlayerFellOff();
	}
}

// Execute GameMode Method (wrapper of a DynamicDelegate.broadcast()). Same principle could be applied to another Engine Class like PlayerState. 
// But i tought that the notify if the Player fell of the map could be related to the map itself (so GameMode).
void ALoadGame::NotifyPlayerFellOff()
{
	ACppExamClaudioDallaiGameMode* CurrentGameMode = Cast<ACppExamClaudioDallaiGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (CurrentGameMode)
	{
		CurrentGameMode->PlayerFellCallback();
	}
}

