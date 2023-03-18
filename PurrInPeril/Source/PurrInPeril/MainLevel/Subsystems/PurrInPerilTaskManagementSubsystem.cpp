// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilTaskManagementSubsystem.h"
#include "PurrInPerilMainGameState.h"
#include "PurrInPerilGameInstance.h"
#include "PurrInPerilTaskActorBase.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Math/Transform.h"

UPurrInPerilTaskManagementSubsystem* UPurrInPerilTaskManagementSubsystem::GetSubsystem(UObject* WorldContextObject)
{
    UWorld* World = WorldContextObject->GetWorld();
    if (World)
    {
        UPurrInPerilTaskManagementSubsystem* Subsys = World->GetSubsystem<UPurrInPerilTaskManagementSubsystem>();
        return Subsys;
    }
    return nullptr;
}

UPurrInPerilTaskManagementSubsystem::UPurrInPerilTaskManagementSubsystem()
    : Super()
{

}

bool UPurrInPerilTaskManagementSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    if (!Super::ShouldCreateSubsystem(Outer))
    {
        return false;
    }

    // Cannot use GetWorld() and get GameState before initialization!
    UWorld* World = Cast<UWorld>(Outer);
    //APurrInPerilMainGameState* GameState = World->GetGameState<APurrInPerilMainGameState>();
    //if (!GameState)
    //{
    //    return false;
    //}

    return true;
}

void UPurrInPerilTaskManagementSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    TaskActors.Empty();
    //InitializeTaskActorsFromWorld();
}

void UPurrInPerilTaskManagementSubsystem::Deinitialize()
{
    TaskActors.Empty();
    Super::Deinitialize();
}

void UPurrInPerilTaskManagementSubsystem::RegisterTaskActor(APurrInPerilTaskActorBase* TaskActor)
{
    FPurrInPerilTaskIdentifier TaskIdentifier;
    if (!GetTaskIdentifier(TaskActor, TaskIdentifier))
    {
        return;
    }

    FPurrInPerilTaskActorSet& TaskActorSet = TaskActors.FindOrAdd(TaskIdentifier);
    TaskActorSet.Set.Add(TaskActor);
}

void UPurrInPerilTaskManagementSubsystem::UnregisterTaskActor(APurrInPerilTaskActorBase* TaskActor)
{
    FPurrInPerilTaskIdentifier TaskIdentifier;
    if (!GetTaskIdentifier(TaskActor, TaskIdentifier))
    {
        return;
    }

    FPurrInPerilTaskActorSet* TaskActorSetPtr = TaskActors.Find(TaskIdentifier);
    if (!TaskActorSetPtr)
    {
        return;
    }

    FPurrInPerilTaskActorSet& TaskActorSet = *TaskActorSetPtr;
    TaskActorSet.Set.Remove(TaskActor);

    if (TaskActorSet.Set.Num() == 0)
    {
        TaskActors.Remove(TaskIdentifier);
    }
}

bool UPurrInPerilTaskManagementSubsystem::GetTaskIdentifier(APurrInPerilTaskActorBase* TaskActor, FPurrInPerilTaskIdentifier& OutTaskIdentifier) const
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return false;
    }
    UPurrInPerilGameInstance* GameInstance = World->GetGameInstance<UPurrInPerilGameInstance>();
    if (!GameInstance || !GameInstance->TaskIdentifierMapping)
    {
        return false;
    }
    OutTaskIdentifier = GameInstance->TaskIdentifierMapping->GetIdentifier(TaskActor->GetClass());
    return true;
}

FPurrInPerilTaskNum UPurrInPerilTaskManagementSubsystem::GetTaskNumAndCompleteCount(const FPurrInPerilTaskIdentifier& TaskIdentifier, AController* Controller) const
{
    FPurrInPerilTaskNum Point = FPurrInPerilTaskNum();
    const FPurrInPerilTaskActorSet* TaskActorSetPtr = TaskActors.Find(TaskIdentifier);
    if (!TaskActorSetPtr)
    {
        return Point;
    }

    const FPurrInPerilTaskActorSet& TaskActorSet = *TaskActorSetPtr;
    Point.TaskNum = TaskActorSet.Set.Num();
    for (const APurrInPerilTaskActorBase* Actor : TaskActorSet.Set)
    {
        if (Actor->IsThisPartOfTaskCompleted(Controller))
        {
            ++Point.TaskCompleteNum;
        }
    }
    return Point;
}

int32 UPurrInPerilTaskManagementSubsystem::GetRemainingTaskIdentifierNotCompleted(TSet<FPurrInPerilTaskIdentifier>& OutRemainingTasks, TSet<FPurrInPerilTaskIdentifier> IgnoringTasks, AController* Controller) const
{
    OutRemainingTasks.Empty(TaskActors.Num());
    int32 RemainingCount = TaskActors.Num();
    for (const auto& Pair : TaskActors)
    {
        if (IgnoringTasks.Contains(Pair.Key))
        {
            --RemainingCount;
        }
        else
        {
            FPurrInPerilTaskNum TaskNumStruct = GetTaskNumAndCompleteCount(Pair.Key, Controller);
            if (TaskNumStruct.TaskCompleteNum == TaskNumStruct.TaskNum)
            {
                --RemainingCount;
            }
            else
            {
                OutRemainingTasks.Add(Pair.Key);
            }
        }
    }
    return RemainingCount;
}

void UPurrInPerilTaskManagementSubsystem::InitializeTaskActorsFromWorld()
{
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }

    for (TActorIterator<APurrInPerilTaskActorBase> It(World); It; ++It)
    {
        RegisterTaskActor(*It);
    }
}
