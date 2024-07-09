// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckPoint.h"

// Sets default values
ACheckPoint::ACheckPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("SaveBoxTrigger"));

    CheckpointText = FText::FromString("CHECKPOINT");
    CheckpointTextRenderer = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CheckPointText"));
    CheckpointTextRenderer->SetupAttachment(BoxTrigger);
    CheckpointTextRenderer->SetText(CheckpointText);
}

// Called when the game starts or when spawned
void ACheckPoint::BeginPlay()
{
	Super::BeginPlay();
    BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &ACheckPoint::OnCollisionCallback);
}

// Called every frame
void ACheckPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ACheckPoint::SaveGame(const FString Slot, const int32 PlayerIndex)
{
    USaveGame* SaveGame = UGameplayStatics::CreateSaveGameObject(UCustomSaveGame::StaticClass());
    if (SaveGame)
    {
        UCustomSaveGame* CheckpointSaveGame = Cast<UCustomSaveGame>(SaveGame);
        if (CheckpointSaveGame)
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

            // Save Datas
            CheckpointSaveGame->PlayerDataStruct.PlayerTransform = PlayerPawn->GetTransform();
            ACharacter* Character = Cast<ACharacter>(PlayerPawn);
            if (Character)
            {
                UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
                if (MovementComponent)
                {
                    CheckpointSaveGame->PlayerDataStruct.PlayerJumpZForce = MovementComponent->JumpZVelocity;
                }
                else
                {
                    CheckpointSaveGame->PlayerDataStruct.PlayerJumpZForce = 600.0f;
                }
            }

            UGameplayStatics::SaveGameToSlot(CheckpointSaveGame, Slot, PlayerIndex);
            return true;
        }
    }

    return false;
}

void ACheckPoint::OnCollisionCallback(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->ActorHasTag(PlayerTag)) 
    {
        SaveGame(SlotName, 0);
    }
}

