// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilWidgetTaskActor.h"
#include "PurrInPerilMainPlayerController.h"


APurrInPerilWidgetTaskActor::APurrInPerilWidgetTaskActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

void APurrInPerilWidgetTaskActor::DoInteraction_Implementation(AController* Controller)
{
    APurrInPerilMainPlayerController* PlayerController = Cast<APurrInPerilMainPlayerController>(Controller);
    if (PlayerController)
    {
        // TODO: 
        // 1. Deactivate player movement. 
        // 2. Open task widget.
    }
}