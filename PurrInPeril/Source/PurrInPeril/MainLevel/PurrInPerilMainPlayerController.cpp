// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilMainPlayerController.h"
#include "PurrInPerilTaskActorBase.h"
#include "PurrInPerilGameInstance.h"
#include "PurrInPerilAsset.h"
#include "PurrInPerilAnimalPawn.h"
#include "PurrInPerilMainGameState.h"
#include "PurrInPerilMainPlayerState.h"
#include "CustomComponents/PurrInPerilSmellDiscoverComponent.h"
#include "Subsystems/PurrInPerilSmellManagementSubsystem.h"
#include "Subsystems/PurrInPerilTaskManagementSubsystem.h"
#include "Widgets/PlayerMainPanelWidgetBase.h"
#include "Blueprint/UserWidget.h"
#include "Engine/World.h"

APurrInPerilMainPlayerController::APurrInPerilMainPlayerController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    //bShowMouseCursor = true;
}

void APurrInPerilMainPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (const UUserWidgetClassSettings* UserWidgetClassSettings = UUserWidgetClassSettings::GetFromGameInstance(this))
    {
        if (!CustomPlayerMainPanelWidgetClass)
        {
            CustomPlayerMainPanelWidgetClass = UserWidgetClassSettings->DefaultPlayerMainPanelWidgetClass;
            if (!CustomPlayerMainPanelWidgetClass)
            {
                CustomPlayerMainPanelWidgetClass = UPlayerMainPanelWidgetBase::StaticClass();
            }
        }

        if (!CustomIndicatorPanelWidgetClass)
        {
            CustomIndicatorPanelWidgetClass = UserWidgetClassSettings->DefaultIndicatorPanelWidgetClass;
            if (!CustomIndicatorPanelWidgetClass)
            {
                CustomIndicatorPanelWidgetClass = UUserWidget::StaticClass();
            }
        }
    }

    if (!PlayerMainPanelWidget)
    {
        PlayerMainPanelWidget = CreateWidget< UPlayerMainPanelWidgetBase>(this, CustomPlayerMainPanelWidgetClass);
    }
    PlayerMainPanelWidget->AddToViewport(PlayerMainPanelWidgetZOrder);

    if (!IndicatorPanelWidget)
    {
        IndicatorPanelWidget = CreateWidget<UUserWidget>(this, CustomIndicatorPanelWidgetClass);
    }
    IndicatorPanelWidget->AddToViewport(IndicatorWidgetZOrder);
    
    APurrInPerilAnimalPawn* LocalPawn = GetPawn<APurrInPerilAnimalPawn>();
    if (LocalPawn && LocalPawn->SmellDiscoverComponent)
    {
        LocalPawn->SmellDiscoverComponent->OnAccurateSmellBegin.AddDynamic(this, &APurrInPerilMainPlayerController::ShowAccurateIndicatorWidget);
        LocalPawn->SmellDiscoverComponent->OnAccurateSmellEnd.AddDynamic(this, &APurrInPerilMainPlayerController::HideAccurateIndicatorWidget);
    }
}

void APurrInPerilMainPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (PlayerMainPanelWidget)
    {
        PlayerMainPanelWidget->RemoveFromParent();
    }
    if (IndicatorPanelWidget)
    {
        IndicatorPanelWidget->RemoveFromParent();
    }
    APurrInPerilAnimalPawn* LocalPawn = GetPawn<APurrInPerilAnimalPawn>();
    if (LocalPawn && LocalPawn->SmellDiscoverComponent)
    {
        LocalPawn->SmellDiscoverComponent->OnAccurateSmellBegin.RemoveDynamic(this, &APurrInPerilMainPlayerController::ShowAccurateIndicatorWidget);
        LocalPawn->SmellDiscoverComponent->OnAccurateSmellEnd.RemoveDynamic(this, &APurrInPerilMainPlayerController::HideAccurateIndicatorWidget);
    }
    Super::EndPlay(EndPlayReason);
}

void APurrInPerilMainPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // All these prodecures move to UserWidget.
    //APurrInPerilAnimalPawn* LocalPawn = GetPawn<APurrInPerilAnimalPawn>();
    //if (LocalPawn && LocalPawn->SmellDiscoverComponent)
    //{
    //    // 1. TODO: Get nearest.
    //    auto* PerceivedNearestSmellProducer = LocalPawn->SmellDiscoverComponent->PerceivedNearestSmellProducer;
    //    // 2. If Pawn's SmellDiscoverComponent bIsActivatingAccurateSmell.
    //    if (LocalPawn->SmellDiscoverComponent->bIsActivatingAccurateSmell)
    //    {
    //        // 3. Activate widget (Already done in OnAccurateSmellBegin).
    //        // 4. Get info from Pawn's SmellDiscoverComponent.
    //        LocalPawn->SmellDiscoverComponent->PerceivedSmellProducers;
    //        // 5. 
    //        // 6. 

    //    }
    //}
}

void APurrInPerilMainPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
}

APurrInPerilAnimalPawn* APurrInPerilMainPlayerController::GetControlledAnimalPawn() const
{
    return Cast<APurrInPerilAnimalPawn>(GetPawn());
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
        SetIgnoreLookInput(true);
        SetShowMouseCursor(true);
        DeactivateInteractableWidget(InteractingTaskActor);
        bIsInteractingWithObject = true;
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
    SetIgnoreMoveInput(bLastIgnoreMoveInput);
    SetIgnoreLookInput(bLastIgnoreMoveInput);
    SetShowMouseCursor(bLastIgnoreMoveInput);
    bLastIgnoreMoveInput = IsMoveInputIgnored();
    ActivateInteractableWidget(InteractingTaskActor);
    bIsInteractingWithObject = false;
}

void APurrInPerilMainPlayerController::ShowAccurateIndicatorWidget()
{

}

void APurrInPerilMainPlayerController::HideAccurateIndicatorWidget()
{

}

bool APurrInPerilMainPlayerController::DoAccurateSmell()
{
    // 1. Check if the player can do accurate smell.
    if (!CheckAccurateSmellValid())
    {
        return false;
    }

    APurrInPerilAnimalPawn* LocalPawn = GetPawn<APurrInPerilAnimalPawn>();
    APurrInPerilMainPlayerState* LocalPlayerState = GetPlayerState<APurrInPerilMainPlayerState>();

    UWorld* World = GetWorld();
    APurrInPerilMainGameState* GameState = World->GetGameState<APurrInPerilMainGameState>();

    // 2. If yes,
    //    3. Decrease hunger value in PlayerState.
    //    4. SmellDiscoverComponent ActivateAccurateSmell(Time).
    LocalPlayerState->AddHungerValue(-GameState->GetInLevelCostParameter().AccurateSmellCost);
    LocalPawn->SmellDiscoverComponent->ActivateAccurateSmell(GameState->GetInLevelTimeParameter().AccurateSmellDurationInSecond);

    return true;
}

bool APurrInPerilMainPlayerController::CheckAccurateSmellValid()
{
    // 1. Pawn's SmellDiscoverComponent bIsActivatingAccurateSmell -> return false.
    // 2. Not enough hunger value -> return false.
    APurrInPerilAnimalPawn* LocalPawn = GetPawn<APurrInPerilAnimalPawn>();
    APurrInPerilMainPlayerState* LocalPlayerState = GetPlayerState<APurrInPerilMainPlayerState>();
    if (!LocalPlayerState || !LocalPawn || !LocalPawn->SmellDiscoverComponent)
    {
        return false;
    }

    UWorld* World = GetWorld();
    if (!World)
    {
        return false;
    }
    APurrInPerilMainGameState* GameState = World->GetGameState<APurrInPerilMainGameState>();
    if (!GameState)
    {
        return false;
    }

    bool bIsActivatingAccurateSmell = LocalPawn->SmellDiscoverComponent->bIsActivatingAccurateSmell;
    if (bIsActivatingAccurateSmell)
    {
        return false;
    }

    if (LocalPlayerState->GetCurrentPlayerStateParameter().HungerValue < GameState->GetInLevelCostParameter().AccurateSmellCost)
    {
        return false;
    }

    return true;
}
