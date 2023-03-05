// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilEnemyPawn.h"
#include "Components/BoxComponent.h"
#include "CustomComponents/PurrInPerilMovementComponent.h"

APurrInPerilEnemyPawn::APurrInPerilEnemyPawn(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SmellProduceComponent = CreateDefaultSubobject<UPurrInPerilSmellProduceComponent>(TEXT("SmellProduceComponent"));
    SmellProduceComponent->SetupAttachment(RootComponent);
}

UPurrInPerilSmellProduceComponent* APurrInPerilEnemyPawn::GetSmellProduceComponent_Implementation()
{
    return SmellProduceComponent;
}
