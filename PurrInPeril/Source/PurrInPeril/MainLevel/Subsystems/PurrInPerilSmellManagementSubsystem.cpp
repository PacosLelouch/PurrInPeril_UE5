// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilSmellManagementSubsystem.h"
#include "PurrInPerilMainGameState.h"
#include "Engine/World.h"
#include "Math/Transform.h"

UPurrInPerilSmellManagementSubsystem* UPurrInPerilSmellManagementSubsystem::GetSubsystem(UObject* WorldContextObject)
{
    UWorld* World = WorldContextObject->GetWorld();
    if (World)
    {
        UPurrInPerilSmellManagementSubsystem* Subsys = World->GetSubsystem<UPurrInPerilSmellManagementSubsystem>();
        return Subsys;
    }
    return nullptr;
}

UPurrInPerilSmellManagementSubsystem::UPurrInPerilSmellManagementSubsystem()
    : Super()
{

}

bool UPurrInPerilSmellManagementSubsystem::ShouldCreateSubsystem(UObject* Outer) const
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

void UPurrInPerilSmellManagementSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    SmellProducers.Empty();
}

void UPurrInPerilSmellManagementSubsystem::Deinitialize()
{
    SmellProducers.Empty();
    Super::Deinitialize();
}

void UPurrInPerilSmellManagementSubsystem::RegisterSmellProducer(UPurrInPerilSmellProduceComponent* SmellProducer)
{
    SmellProducers.Add(SmellProducer);
}

void UPurrInPerilSmellManagementSubsystem::UnregisterSmellProducer(UPurrInPerilSmellProduceComponent* SmellProducer)
{
    SmellProducers.Remove(SmellProducer);
}

UPurrInPerilSmellProduceComponent* UPurrInPerilSmellManagementSubsystem::GetSmellProducersInDistance(
    TMap<UPurrInPerilSmellProduceComponent*, float>& OutSmellProducers, 
    USceneComponent* OriginSceneComponent, float MaxDistance, 
    bool bNeedMap, bool bWithNoSmell, bool bWithOrigin)
{
    OutSmellProducers.Empty(SmellProducers.Num());
    if (SmellProducers.Num() == 0 || !OriginSceneComponent)
    {
        return nullptr;
    }

    float MinDistance = -1.0f;
    UPurrInPerilSmellProduceComponent* ClosestComponent = nullptr;

    FTransform OriginTransform = OriginSceneComponent->GetComponentTransform();
    for (UPurrInPerilSmellProduceComponent* SmellProducer : SmellProducers)
    {
        if (!bWithNoSmell && !SmellProducer->bWithSmell)
        {
            continue;
        }
        if (!bWithOrigin && SmellProducer == OriginSceneComponent)
        {
            continue;
        }
        FTransform SmellProducerTransform = SmellProducer->GetComponentTransform();
        float Distance = (OriginTransform.GetLocation() - SmellProducerTransform.GetLocation()).Size();
        if (Distance < MaxDistance)
        {
            if (bNeedMap)
            {
                OutSmellProducers.Add(SmellProducer, Distance);
            }
            if (!ClosestComponent || Distance < MinDistance)
            {
                ClosestComponent = SmellProducer;
                MinDistance = Distance;
            }
        }
    }
    return ClosestComponent;
}
