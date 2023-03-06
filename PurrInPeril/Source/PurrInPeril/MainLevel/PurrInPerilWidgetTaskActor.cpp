// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilWidgetTaskActor.h"
#include "PurrInPerilMainPlayerController.h"
#include "Blueprint/UserWidget.h"


APurrInPerilWidgetTaskActor::APurrInPerilWidgetTaskActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void APurrInPerilWidgetTaskActor::OpenInteraction_Implementation(AController* Controller)
{
	APurrInPerilMainPlayerController* PlayerController = Cast<APurrInPerilMainPlayerController>(Controller);
	if (PlayerController)
	{
		UUserWidget* WidgetForPlayer = nullptr;
		UUserWidget** WidgetForPlayerPtr = PlayerToTaskWidgets.Find(PlayerController);
		if (WidgetForPlayerPtr)
		{
			WidgetForPlayer = *WidgetForPlayerPtr;
		}
		else
		{
			WidgetForPlayer = CreateWidget(PlayerController, TaskWidgetClass);
			PlayerToTaskWidgets.Add(PlayerController, WidgetForPlayer);
		}
		PlayerController->OpenWidgetLockMovement(WidgetForPlayer);
	}
}

void APurrInPerilWidgetTaskActor::CloseInteraction_Implementation(AController* Controller)
{
	APurrInPerilMainPlayerController* PlayerController = Cast<APurrInPerilMainPlayerController>(Controller);
	if (PlayerController)
	{
		UUserWidget** WidgetForPlayerPtr = PlayerToTaskWidgets.Find(PlayerController);
		if (WidgetForPlayerPtr)
		{
			UUserWidget* WidgetForPlayer = *WidgetForPlayerPtr;
			PlayerController->CloseWidgetUnlockMovement(WidgetForPlayer);
		}
	}
}