// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilEnemyPawn.h"
#include "Components/BoxComponent.h"
#include "CustomComponents/PurrInPerilMovementComponent.h"
#include "PurrInPerilAsset.h"

APurrInPerilEnemyPawn::APurrInPerilEnemyPawn(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SmellProduceComponent = CreateDefaultSubobject<UPurrInPerilSmellProduceComponent>(TEXT("SmellProduceComponent"));
    SmellProduceComponent->SetupAttachment(RootComponent);
}

void APurrInPerilEnemyPawn::BeginPlay()
{
    Super::BeginPlay();
    if (auto* GameplayNumericalSettings = UGameplayNumericalSettings::GetFromGameInstance(this))
    {
        if (!bOverrideInLevelEnemyParameter)
        {
            InLevelEnemyParameter = GameplayNumericalSettings->DefaultInLevelEnemyParameter;
        }
    }
}

UPurrInPerilSmellProduceComponent* APurrInPerilEnemyPawn::GetSmellProduceComponent_Implementation()
{
    return SmellProduceComponent;
}
