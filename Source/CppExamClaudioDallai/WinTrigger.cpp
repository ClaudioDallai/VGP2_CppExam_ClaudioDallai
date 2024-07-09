// Fill out your copyright notice in the Description page of Project Settings.


#include "WinTrigger.h"

// Sets default values
AWinTrigger::AWinTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("WinTrigger"));

	WinText = FText::FromString("WIN AND RESTART");
	WinTextRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("WinText"));
	WinTextRenderer->SetupAttachment(BoxTrigger);
	WinTextRenderer->SetText(WinText);
}

// Called when the game starts or when spawned
void AWinTrigger::BeginPlay()
{
	Super::BeginPlay();

	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AWinTrigger::OnCollisionCallback);
}

// Called every frame
void AWinTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWinTrigger::OnCollisionCallback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag(PlayerTag))
	{
		DeleteCurrentSaveSlot(SlotName, 0);
		RestartLevelAfterWin();
	}
}

void AWinTrigger::RestartLevelAfterWin()
{
	UGameplayStatics::OpenLevel(this, LevelToOpen, true);
}

void AWinTrigger::DeleteCurrentSaveSlot(const FString Slot, const int32 PlayerIndex)
{
	if (UGameplayStatics::DoesSaveGameExist(Slot, PlayerIndex))
	{
		UGameplayStatics::DeleteGameInSlot(Slot, PlayerIndex);
	}
}

