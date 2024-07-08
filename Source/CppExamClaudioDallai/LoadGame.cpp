// Fill out your copyright notice in the Description page of Project Settings.


#include "LoadGame.h"

// Sets default values
ALoadGame::ALoadGame()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("LoadBoxTrigger"));
}

// Called when the game starts or when spawned
void ALoadGame::BeginPlay()
{
	Super::BeginPlay();
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ALoadGame::OnCollisionCallback);
}

// Called every frame
void ALoadGame::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ALoadGame::LoadGame(const FString Slot, const int32 PlayerIndex)
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

		return true;
	}

	return false;
}

void ALoadGame::OnCollisionCallback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag(PlayerTag))
	{
		LoadGame(SlotName, 0);
	}
}

