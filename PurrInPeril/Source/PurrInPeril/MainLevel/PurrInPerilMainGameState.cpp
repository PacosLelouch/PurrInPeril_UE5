// Copyright Epic Games, Inc. All Rights Reserved.


#include "PurrInPerilMainGameState.h"
#include "PurrInPerilAsset.h"

APurrInPerilMainGameState::APurrInPerilMainGameState(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
}

void APurrInPerilMainGameState::BeginPlay()
{
    Super::BeginPlay();
    if (auto* GameplayNumericalSettings = UGameplayNumericalSettings::GetFromGameInstance(this))
    {
        if (!bOverrideInLevelCostParameter)
        {
            InLevelCostParameter = GameplayNumericalSettings->DefaultInLevelCostParameter;
        }
        if (!bOverrideInLevelTimeParameter)
        {
            InLevelTimeParameter = GameplayNumericalSettings->DefaultInLevelTimeParameter;
        }
    }

    CurrentCountdownInSecond = InLevelTimeParameter.InitialGameCountdownInSecond;
}

void APurrInPerilMainGameState::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    UWorld* World = GetWorld();
    if (!World)
    {
        return;
    }
    if (!World->IsPaused() && !IsGameOver() && CurrentCountdownInSecond > 0.0f)
    {
        CurrentCountdownInSecond = FMath::Max(0.0f, CurrentCountdownInSecond - DeltaSeconds);
    }
}

void APurrInPerilMainGameState::SetIsGameOver(const bool bValue)
{
    bIsGameOver = bValue;
}
