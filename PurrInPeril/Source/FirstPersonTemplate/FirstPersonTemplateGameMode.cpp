// Copyright Epic Games, Inc. All Rights Reserved.

#include "FirstPersonTemplateGameMode.h"
#include "FirstPersonTemplateCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFirstPersonTemplateGameMode::AFirstPersonTemplateGameMode()
	: Super()
{
	// Not recommended to do this.
	//// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	//DefaultPawnClass = PlayerPawnClassFinder.Class;

}
