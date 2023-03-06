// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilMainPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "PurrInPerilTaskActorBase.h"

APurrInPerilMainPlayerController::APurrInPerilMainPlayerController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bShowMouseCursor = true;
}

void APurrInPerilMainPlayerController::BeginPlay()
{
    Super::BeginPlay();
}

void APurrInPerilMainPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // TODO in Tick:
    // 1. Get nearest.
    // 1. If Pawn's SmellDiscoverComponent bIsActivatingAccurateSmell.
    //    2. Activate widget.
    //    2. Get info from Pawn's SmellDiscoverComponent.
    //    3. 
    //    4. 
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
            HoldingWidget->AddToViewport(InteractableWidgetZOrder);
            InteractingTaskActor = TaskActorToActivate;
        }
    }
    // Do not create widget for task actor. It should create the widget before activation.

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

void APurrInPerilMainPlayerController::OpenWidgetLockMovement(UUserWidget* UserWidget)
{
    if (UserWidget)
    {
        // 1. Deactivate player movement. 
        // 2. Open task widget.
        UserWidget->AddToViewport(WidgetLockMovementZOrder);
        bLastIgnoreMoveInput = IsMoveInputIgnored();
        SetIgnoreMoveInput(true);
    }
}

void APurrInPerilMainPlayerController::CloseWidgetUnlockMovement(UUserWidget* UserWidget) 
{
    if (UserWidget)
    {
        // 1. Activate player movement. 
        // 2. Close task widget.
        UserWidget->RemoveFromParent();
    }
    bLastIgnoreMoveInput = IsMoveInputIgnored();
    SetIgnoreMoveInput(bLastIgnoreMoveInput);
}

bool APurrInPerilMainPlayerController::DoAccurateSmell()
{
    // 1. Check if the player can do accurate smell.
    if (!CheckAccurateSmellValid())
    {
        return false;
    }
    // TODO:
    // 2. If yes,
    //    3. Decrease hunger value in PlayerState.
    //    4. SmellDiscoverComponent ActivateAccurateSmell(Time).

    return true;
}

bool APurrInPerilMainPlayerController::CheckAccurateSmellValid()
{
    // TODO:
    // 1. Pawn's SmellDiscoverComponent !bIsActivatingAccurateSmell.
    // 2. Enough hunger value.
    return false;
}
