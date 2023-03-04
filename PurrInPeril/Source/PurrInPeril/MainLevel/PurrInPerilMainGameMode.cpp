// Copyright Epic Games, Inc. All Rights Reserved.


#include "PurrInPerilMainGameMode.h"
#include "PurrInPerilMainGameState.h"
#include "PurrInPerilMainPlayerController.h"
#include "PurrInPerilMainPlayerState.h"
#include "PurrInPerilAnimalPawn.h"

APurrInPerilMainGameMode::APurrInPerilMainGameMode(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    GameStateClass = APurrInPerilMainGameState::StaticClass();
    PlayerControllerClass = APurrInPerilMainPlayerController::StaticClass();
    DefaultPawnClass = APurrInPerilAnimalPawn::StaticClass();
    PlayerStateClass = APurrInPerilMainPlayerState::StaticClass();
}
