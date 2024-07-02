// Copyright Epic Games, Inc. All Rights Reserved.

#include "CppExamClaudioDallaiGameMode.h"
#include "CppExamClaudioDallaiCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACppExamClaudioDallaiGameMode::ACppExamClaudioDallaiGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
