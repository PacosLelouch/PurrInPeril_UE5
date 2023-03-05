// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilInteractableComponent.h"

namespace
{
    static const FColor TriggerBaseColor(100, 255, 100, 255);
    static const FName TriggerCollisionProfileName(TEXT("Trigger"));
}

UPurrInPerilInteractableComponent::UPurrInPerilInteractableComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    ShapeColor = TriggerBaseColor;
    SetGenerateOverlapEvents(true);
    SetCollisionProfileName(TriggerCollisionProfileName);
}
