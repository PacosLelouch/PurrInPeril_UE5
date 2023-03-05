// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilSmellProduceComponent.h"
#include "Subsystems/PurrInPerilSmellManagementSubsystem.h"

UPurrInPerilSmellProduceComponent::UPurrInPerilSmellProduceComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

void UPurrInPerilSmellProduceComponent::BeginPlay()
{
    Super::BeginPlay();

    auto* SmellManagementSubsystem = UPurrInPerilSmellManagementSubsystem::GetSubsystem(this);
    if (SmellManagementSubsystem)
    {
        SmellManagementSubsystem->RegisterSmellProducer(this);
    }
}

void UPurrInPerilSmellProduceComponent::EndPlay(EEndPlayReason::Type EndPlayReason)
{
    auto* SmellManagementSubsystem = UPurrInPerilSmellManagementSubsystem::GetSubsystem(this);
    if (SmellManagementSubsystem)
    {
        SmellManagementSubsystem->UnregisterSmellProducer(this);
    }

    Super::EndPlay(EndPlayReason);
}
