// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilMainPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "PurrInPerilTaskActorBase.h"

APurrInPerilMainPlayerController::APurrInPerilMainPlayerController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bShowMouseCursor = true;
}

bool APurrInPerilMainPlayerController::ActivateInteractableWidget(APurrInPerilTaskActorBase* TaskActorToActivate)
{
    if (!TaskActorToActivate)
    {
        return false;
    }

    if (InteractingTaskActor)
    {
        if (InteractingTaskActor != TaskActorToActivate)
        {
            UUserWidget** HoldingWidgetPtr = InteractingTaskActor->PlayerToInteractTipsWidgets.Find(this);
            if (HoldingWidgetPtr)
            {
                UUserWidget* HoldingWidget = *HoldingWidgetPtr;
                HoldingWidget->RemoveFromParent();
            }
        }
    }

    UUserWidget** HoldingWidgetPtr = TaskActorToActivate->PlayerToInteractTipsWidgets.Find(this);
    if (HoldingWidgetPtr)
    {
        //if (InteractingTaskActor != TaskActorToActivate)
        {
            UUserWidget* HoldingWidget = *HoldingWidgetPtr;
            HoldingWidget->AddToViewport();
            InteractingTaskActor = TaskActorToActivate;
        }
    }
    else
    {
        UUserWidget* NewWidget = CreateWidget(this, TaskActorToActivate->CustomInteractTipsClass);
        NewWidget->AddToViewport();
        TaskActorToActivate->PlayerToInteractTipsWidgets.Add(this, NewWidget);
        InteractingTaskActor = TaskActorToActivate;
    }

    return true;
}

bool APurrInPerilMainPlayerController::DeactivateInteractableWidget(APurrInPerilTaskActorBase* TaskActorToActivate)
{
    if (!TaskActorToActivate)
    {
        return false;
    }

    if (InteractingTaskActor)
    {
        if (InteractingTaskActor == TaskActorToActivate)
        {
            UUserWidget** HoldingWidgetPtr = InteractingTaskActor->PlayerToInteractTipsWidgets.Find(this);
            if (HoldingWidgetPtr)
            {
                UUserWidget* HoldingWidget = *HoldingWidgetPtr;
                HoldingWidget->RemoveFromParent();
                return true;
            }
        }
    }

    return false;
}
