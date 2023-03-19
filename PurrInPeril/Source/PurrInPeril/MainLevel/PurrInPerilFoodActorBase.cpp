// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilFoodActorBase.h"
#include "Engine/GameEngine.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"
#include "PurrInPerilGameInstance.h"
#include "PurrInPerilAsset.h"
#include "PurrInPerilMainPlayerController.h"


APurrInPerilFoodActorBase::APurrInPerilFoodActorBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
    InteractableComponent = CreateDefaultSubobject<UPurrInPerilInteractableComponent>(TEXT("InteractableComponent"));
    InteractableComponent->SetupAttachment(RootComponent);

    SmellProduceComponent = CreateDefaultSubobject<UPurrInPerilSmellProduceComponent>(TEXT("SmellProduceComponent"));
    SmellProduceComponent->SetupAttachment(RootComponent);
}

void APurrInPerilFoodActorBase::BeginPlay()
{
    Super::BeginPlay();
}

void APurrInPerilFoodActorBase::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }
    if (!World->IsPaused() && CurrentInteractColdDownInSecond > 0.0f)
    {
        CurrentInteractColdDownInSecond = FMath::Max(0.0f, CurrentInteractColdDownInSecond - DeltaSeconds);
    }
}

void APurrInPerilFoodActorBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}

UPurrInPerilInteractableComponent* APurrInPerilFoodActorBase::GetInteractableComponent_Implementation()
{
    return InteractableComponent;
}

UPurrInPerilSmellProduceComponent* APurrInPerilFoodActorBase::GetSmellProduceComponent_Implementation()
{
    return SmellProduceComponent;
}

void APurrInPerilFoodActorBase::OpenInteraction_Implementation(AController* Controller)
{
    if (IsColdDownCompleted())
    {
        CurrentInteractColdDownInSecond += MaxInteractColdDownInSecond;
        if (Durability > 0)
        {
            --Durability;
        }
        OnFoodInteractWithPlayer(Controller, true);
        if (Durability == 0)
        {
            Destroy();
        }
    }
    else
    {
        OnFoodInteractWithPlayer(Controller, false);
    }
}

void APurrInPerilFoodActorBase::CloseInteraction_Implementation(AController* Controller)
{
}

void APurrInPerilFoodActorBase::OnFoodInteractWithPlayer_Implementation(AController* Controller, bool bSucceeded)
{

}

bool APurrInPerilFoodActorBase::IsColdDownCompleted() const
{
    return CurrentInteractColdDownInSecond <= 0.0f && Durability != 0;
}
