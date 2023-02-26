// Copyright Epic Games, Inc. All Rights Reserved.

#include "PracticeUnrealGASGameMode.h"
#include "PracticeUnrealGASCharacter.h"
#include "UObject/ConstructorHelpers.h"

APracticeUnrealGASGameMode::APracticeUnrealGASGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
