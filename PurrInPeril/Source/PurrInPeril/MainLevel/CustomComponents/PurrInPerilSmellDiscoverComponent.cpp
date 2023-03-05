// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilSmellDiscoverComponent.h"
#include "PurrInPerilSmellProduceComponent.h"
#include "Subsystems/PurrInPerilSmellManagementSubsystem.h"
#include "Engine/World.h"
#include "TimerManager.h"

UPurrInPerilSmellDiscoverComponent::UPurrInPerilSmellDiscoverComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UPurrInPerilSmellDiscoverComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UPurrInPerilSmellDiscoverComponent::EndPlay(EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
}

void UPurrInPerilSmellDiscoverComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    auto* SmellManagementSubsystem = UPurrInPerilSmellManagementSubsystem::GetSubsystem(this);
    if (SmellManagementSubsystem)
    {
        // 1. Find the closest smell producer.
        // 2. If bIsActivatingAccurateSmell, find smell producers in specific range.
        PerceivedClosestSmellProducer = SmellManagementSubsystem->GetSmellProducersInDistance(PerceivedSmellProducers, this, MaxSmellDistance, bIsActivatingAccurateSmell);
    }
}

void UPurrInPerilSmellDiscoverComponent::ActivateAccurateSmell(float Time)
{
    bIsActivatingAccurateSmell = true;
    UWorld* World = GetWorld();
    if (World)
    {
        FTimerManager& TimerManager = World->GetTimerManager();
        TimerManager.SetTimer(
                AccurateTimerHandle,
                [this]() {
                    bIsActivatingAccurateSmell = false;
                    AccurateTimerHandle.Invalidate();
                },
                Time,
                false,
                0.0f);
    }
}
