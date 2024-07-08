// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "CustomSaveGame.generated.h"

USTRUCT(BlueprintType)
struct FPlayerSaveData {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FTransform PlayerTransform;
};


/**
 * 
 */
UCLASS()
class CPPEXAMCLAUDIODALLAI_API UCustomSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	FPlayerSaveData PlayerDataStruct;
};
