// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CppExamClaudioDallaiGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerFellOff);

UCLASS(minimalapi)
class ACppExamClaudioDallaiGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACppExamClaudioDallaiGameMode();

	UFUNCTION()
	bool GetIsLoaded();

	UFUNCTION()
	void SetIsLoaded(bool bNewLoaded);

	UFUNCTION()
	void PlayerFellCallback();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPlayerFellOff OnPlayerFellOff;

private:
	bool bIsLoaded;

};



