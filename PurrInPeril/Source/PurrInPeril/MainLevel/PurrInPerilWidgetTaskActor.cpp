// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilWidgetTaskActor.h"
#include "PurrInPerilMainPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/TaskContentWidgetBase.h"


APurrInPerilWidgetTaskActor::APurrInPerilWidgetTaskActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void APurrInPerilWidgetTaskActor::OpenInteraction_Implementation(AController* Controller)
{
	APurrInPerilMainPlayerController* PlayerController = Cast<APurrInPerilMainPlayerController>(Controller);
	if (PlayerController)
	{
		UTaskContentWidgetBase* WidgetForPlayer = nullptr;
		UTaskContentWidgetBase** WidgetForPlayerPtr = PlayerToTaskWidgets.Find(PlayerController);
		if (WidgetForPlayerPtr)
		{
			WidgetForPlayer = *WidgetForPlayerPtr;
		}
		else
		{
			WidgetForPlayer = CreateWidget<UTaskContentWidgetBase>(PlayerController, TSubclassOf<UUserWidget>(TaskWidgetClass));
			WidgetForPlayer->SetTaskOwner(this);
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
		UTaskContentWidgetBase** WidgetForPlayerPtr = PlayerToTaskWidgets.Find(PlayerController);
		if (WidgetForPlayerPtr)
		{
			UTaskContentWidgetBase* WidgetForPlayer = *WidgetForPlayerPtr;
			PlayerController->CloseWidgetUnlockMovement(WidgetForPlayer);
		}
	}
}