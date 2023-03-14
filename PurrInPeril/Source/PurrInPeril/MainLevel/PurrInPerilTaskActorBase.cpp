// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilTaskActorBase.h"
#include "Engine/GameEngine.h"
#include "Engine/World.h"
#include "Blueprint/UserWidget.h"
#include "PurrInPerilGameInstance.h"
#include "PurrInPerilAsset.h"
#include "PurrInPerilMainPlayerController.h"
#include "Subsystems/PurrInPerilTaskManagementSubsystem.h"


APurrInPerilTaskActorBase::APurrInPerilTaskActorBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
    InteractableComponent = CreateDefaultSubobject<UPurrInPerilInteractableComponent>(TEXT("InteractableComponent"));
    InteractableComponent->SetupAttachment(RootComponent);

    SmellProduceComponent = CreateDefaultSubobject<UPurrInPerilSmellProduceComponent>(TEXT("SmellProduceComponent"));
    SmellProduceComponent->SetupAttachment(RootComponent);
}

void APurrInPerilTaskActorBase::BeginPlay()
{
    Super::BeginPlay();

    UPurrInPerilTaskManagementSubsystem* TaskManagementSubsystem = UPurrInPerilTaskManagementSubsystem::GetSubsystem(this);
    if (TaskManagementSubsystem)
    {
        TaskManagementSubsystem->RegisterTaskActor(this);
    }
}

void APurrInPerilTaskActorBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    UPurrInPerilTaskManagementSubsystem* TaskManagementSubsystem = UPurrInPerilTaskManagementSubsystem::GetSubsystem(this);
    if (TaskManagementSubsystem)
    {
        TaskManagementSubsystem->UnregisterTaskActor(this);
    }
    Super::EndPlay(EndPlayReason);
}

UPurrInPerilInteractableComponent* APurrInPerilTaskActorBase::GetInteractableComponent_Implementation()
{
    return InteractableComponent;
}

UPurrInPerilSmellProduceComponent* APurrInPerilTaskActorBase::GetSmellProduceComponent_Implementation()
{
    return SmellProduceComponent;
}

void APurrInPerilTaskActorBase::CompleteThisPartOfTask(AController* Controller)
{
    CompleteThisPartOfTask_Implementation(Controller);
    BP_CompleteThisPartOfTask(Controller);
}

void APurrInPerilTaskActorBase::CompleteThisPartOfTask_Implementation(AController* Controller)
{
    bool* bIsCompletedPtr = PlayerToPartOfTaskCompleted.Find(Controller);
    if (bIsCompletedPtr)
    {
        *bIsCompletedPtr = true;
    }
    else
    {
        PlayerToPartOfTaskCompleted.Add(Controller, true);
    }
    SmellProduceComponent->bWithSmell = false;
    if (APurrInPerilMainPlayerController* PlayerController = Cast<APurrInPerilMainPlayerController>(Controller))
    {
        PlayerController->OnPartOfTaskComplete.Broadcast(this);
    }
}

void APurrInPerilTaskActorBase::ResetThisPartOfTask(AController* Controller)
{
    ResetThisPartOfTask_Implementation(Controller);
    BP_ResetThisPartOfTask(Controller);
}

void APurrInPerilTaskActorBase::ResetThisPartOfTask_Implementation(AController* Controller)
{
    bool* bIsCompletedPtr = PlayerToPartOfTaskCompleted.Find(Controller);
    if (bIsCompletedPtr)
    {
        *bIsCompletedPtr = false;
    }
    else
    {
        PlayerToPartOfTaskCompleted.Add(Controller, false);
    }
    SmellProduceComponent->bWithSmell = true;
    if (APurrInPerilMainPlayerController* PlayerController = Cast<APurrInPerilMainPlayerController>(Controller))
    {
        PlayerController->OnPartOfTaskReset.Broadcast(this);
    }
}

bool APurrInPerilTaskActorBase::IsThisPartOfTaskCompleted(AController* Controller) const
{
    const bool* bIsCompletedPtr = PlayerToPartOfTaskCompleted.Find(Controller);
    return bIsCompletedPtr && *bIsCompletedPtr;
}
