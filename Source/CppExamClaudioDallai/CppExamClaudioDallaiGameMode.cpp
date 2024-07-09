// Copyright Epic Games, Inc. All Rights Reserved.

#include "CppExamClaudioDallaiGameMode.h"
#include "UObject/ConstructorHelpers.h"

ACppExamClaudioDallaiGameMode::ACppExamClaudioDallaiGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Custom/Blueprints/Player/BP_Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	bIsLoaded = false;
}

bool ACppExamClaudioDallaiGameMode::GetIsLoaded()
{
	return bIsLoaded;
}

void ACppExamClaudioDallaiGameMode::SetIsLoaded(bool bNewLoaded)
{
	bIsLoaded = bNewLoaded;
}

void ACppExamClaudioDallaiGameMode::PlayerFellCallback()
{
	OnPlayerFellOff.Broadcast();
}
