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
    if (Durability > 0)
    {
        --Durability;
    }
    if (Durability == 0)
    {
        Destroy();
    }
}

void APurrInPerilFoodActorBase::CloseInteraction_Implementation(AController* Controller)
{
}
