// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilSmellDiscoverComponent.h"
#include "PurrInPerilSmellProduceComponent.h"
#include "PurrInPerilGameInstance.h"
#include "PurrInPerilAsset.h"
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

    //bIsActivatingAccurateSmell = true;
    //UE_LOG(LogTemp, Warning, TEXT("[%s] Set bIsActivatingAccurateSmell = true for debugging. Remember to reset this value after debugging."), *GetName());

    if (!bOverrideSmellDistanceParameter)
    {
        if (auto* GameplayNumericalSettings = UGameplayNumericalSettings::GetFromGameInstance(this))
        {
            SmellDistanceParameter = GameplayNumericalSettings->DefaultSmellDistanceParameter;
        }
    }
}

void UPurrInPerilSmellDiscoverComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
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
        PerceivedNearestSmellProducer = SmellManagementSubsystem->GetSmellProducersInDistance(PerceivedSmellProducers, this, SmellDistanceParameter.MaxSmellDistance, bIsActivatingAccurateSmell, false, false);
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
                    OnAccurateSmellEnd.Broadcast();
                },
                Time,
                false,
                Time);
        OnAccurateSmellBegin.Broadcast();
    }
}
