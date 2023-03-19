// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilMainPlayerController.h"
#include "PurrInPerilTaskActorBase.h"
#include "PurrInPerilGameInstance.h"
#include "PurrInPerilAsset.h"
#include "PurrInPerilAnimalPawn.h"
#include "PurrInPerilMainGameState.h"
#include "PurrInPerilMainPlayerState.h"
#include "CustomComponents/PurrInPerilSmellDiscoverComponent.h"
#include "CustomComponents/PurrInPerilInteractableComponent.h"
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
    //SetInputMode(FInputModeGameAndUI().SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways));//TEST

    if (const UUserWidgetClassSettings* UserWidgetClassSettings = UUserWidgetClassSettings::GetFromGameInstance(this))
    {
        if (!CustomPlayerMainBackgroundPanelWidgetClass)
        {
            CustomPlayerMainBackgroundPanelWidgetClass = UserWidgetClassSettings->DefaultPlayerMainBackgroundPanelWidgetClass;
            if (!CustomPlayerMainBackgroundPanelWidgetClass)
            {
                CustomPlayerMainBackgroundPanelWidgetClass = UPlayerMainPanelWidgetBase::StaticClass();
            }
        }
        if (!CustomPlayerMainForegroundPanelWidgetClass)
        {
            CustomPlayerMainForegroundPanelWidgetClass = UserWidgetClassSettings->DefaultPlayerMainForegroundPanelWidgetClass;
            if (!CustomPlayerMainForegroundPanelWidgetClass)
            {
                CustomPlayerMainForegroundPanelWidgetClass = UPlayerMainPanelWidgetBase::StaticClass();
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

    if (!PlayerMainBackgroundPanelWidget)
    {
        PlayerMainBackgroundPanelWidget = CreateWidget< UPlayerMainPanelWidgetBase>(this, CustomPlayerMainBackgroundPanelWidgetClass);
    }
    PlayerMainBackgroundPanelWidget->AddToViewport(PlayerMainBackgroundPanelWidgetZOrder);
    if (!PlayerMainForegroundPanelWidget)
    {
        PlayerMainForegroundPanelWidget = CreateWidget< UPlayerMainPanelWidgetBase>(this, CustomPlayerMainForegroundPanelWidgetClass);
    }
    PlayerMainForegroundPanelWidget->AddToViewport(PlayerMainForegroundPanelWidgetZOrder);

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
    if (PlayerMainForegroundPanelWidget)
    {
        PlayerMainForegroundPanelWidget->RemoveFromParent();
    }
    if (PlayerMainBackgroundPanelWidget)
    {
        PlayerMainBackgroundPanelWidget->RemoveFromParent();
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

bool APurrInPerilMainPlayerController::ActivateInteractableWidget(UPurrInPerilInteractableComponent* ComponentToOpenInteraction)
{
    if (!ComponentToOpenInteraction)
    {
        return false;
    }

    if (InteractingComponent)
    {
        if (InteractingComponent != ComponentToOpenInteraction)
        {
            UUserWidget** HoldingWidgetPtr = InteractingComponent->PlayerToInteractTipsWidgets.Find(this);
            if (HoldingWidgetPtr)
            {
                UUserWidget* HoldingWidget = *HoldingWidgetPtr;
                HoldingWidget->RemoveFromParent();
            }
        }
    }

    UUserWidget** HoldingWidgetPtr = ComponentToOpenInteraction->PlayerToInteractTipsWidgets.Find(this);
    if (HoldingWidgetPtr)
    {
        //if (InteractingComponent != ComponentToOpenInteraction)
        {
            UUserWidget* HoldingWidget = *HoldingWidgetPtr;
            HoldingWidget->AddToViewport(InteractableWidgetZOrder);
            InteractingComponent = ComponentToOpenInteraction;
        }
    }
    // Do not create widget for task actor. It should create the widget before activation.

    return true;
}

bool APurrInPerilMainPlayerController::DeactivateInteractableWidget(UPurrInPerilInteractableComponent* ComponentToCloseInteraction)
{
    if (!ComponentToCloseInteraction)
    {
        return false;
    }

    if (InteractingComponent)
    {
        if (InteractingComponent == ComponentToCloseInteraction)
        {
            InteractingComponent = nullptr;
            UUserWidget** HoldingWidgetPtr = ComponentToCloseInteraction->PlayerToInteractTipsWidgets.Find(this);
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
        DeactivateInteractableWidget(InteractingComponent);
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
    ActivateInteractableWidget(InteractingComponent);
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

bool APurrInPerilMainPlayerController::AddSanityValue(float AddValue)
{
    if (APurrInPerilMainPlayerState* LocalPlayerState = GetPlayerState<APurrInPerilMainPlayerState>())
    {
        return LocalPlayerState->AddSanityValue(AddValue);
    }
    return false;
}

bool APurrInPerilMainPlayerController::AddHungerValue(float AddValue)
{
    if (APurrInPerilMainPlayerState* LocalPlayerState = GetPlayerState<APurrInPerilMainPlayerState>())
    {
        return LocalPlayerState->AddHungerValue(AddValue);
    }
    return false;
}
