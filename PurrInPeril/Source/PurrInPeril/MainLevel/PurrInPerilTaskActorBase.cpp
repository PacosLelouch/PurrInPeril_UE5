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

#if WITH_EDITORONLY_DATA
    Sync_IsTaskCompleted_Debugging(Controller);
#endif // WITH_EDITORONLY_DATA
}

void APurrInPerilTaskActorBase::CompleteThisPartOfTask_Implementation(AController* Controller)
{
#if TASK_COUNTED_PER_PLAYER
    bool* bIsCompletedPtr = PlayerToPartOfTaskCompleted.Find(Controller);
    if (bIsCompletedPtr)
    {
        *bIsCompletedPtr = true;
    }
    else
    {
        PlayerToPartOfTaskCompleted.Add(Controller, true);
    }
#else // !TASK_COUNTED_PER_PLAYER
    bIsTaskCompleted = true;
#endif // TASK_COUNTED_PER_PLAYER
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

#if WITH_EDITORONLY_DATA
    Sync_IsTaskCompleted_Debugging(Controller);
#endif // WITH_EDITORONLY_DATA
}

void APurrInPerilTaskActorBase::ResetThisPartOfTask_Implementation(AController* Controller)
{
#if TASK_COUNTED_PER_PLAYER
    bool* bIsCompletedPtr = PlayerToPartOfTaskCompleted.Find(Controller);
    if (bIsCompletedPtr)
    {
        *bIsCompletedPtr = false;
    }
    else
    {
        PlayerToPartOfTaskCompleted.Add(Controller, false);
    }
#else // !TASK_COUNTED_PER_PLAYER
    bIsTaskCompleted = false;
#endif // TASK_COUNTED_PER_PLAYER
    SmellProduceComponent->bWithSmell = true;
    if (APurrInPerilMainPlayerController* PlayerController = Cast<APurrInPerilMainPlayerController>(Controller))
    {
        PlayerController->OnPartOfTaskReset.Broadcast(this);
    }
}

bool APurrInPerilTaskActorBase::IsThisPartOfTaskCompleted(AController* Controller) const
{
#if TASK_COUNTED_PER_PLAYER
    const bool* bIsCompletedPtr = PlayerToPartOfTaskCompleted.Find(Controller);
    return bIsCompletedPtr && *bIsCompletedPtr;
#else // !TASK_COUNTED_PER_PLAYER
    return bIsTaskCompleted;
#endif // TASK_COUNTED_PER_PLAYER
}

#if WITH_EDITORONLY_DATA
void APurrInPerilTaskActorBase::Sync_IsTaskCompleted_Debugging(AController* Controller)
{
#if TASK_COUNTED_PER_PLAYER
    const bool* bIsCompletedPtr = PlayerToPartOfTaskCompleted.Find(Controller);
    bIsTaskCompleted_Debugging = bIsCompletedPtr && *bIsCompletedPtr;
#else // !TASK_COUNTED_PER_PLAYER
    bIsTaskCompleted_Debugging = bIsTaskCompleted;
#endif // TASK_COUNTED_PER_PLAYER
}
#endif // WITH_EDITORONLY_DATA
