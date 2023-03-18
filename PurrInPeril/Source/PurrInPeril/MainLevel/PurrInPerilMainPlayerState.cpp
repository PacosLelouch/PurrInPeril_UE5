// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilMainPlayerState.h"
#include "PurrInPerilMainGameState.h"
#include "PurrInPerilAnimalPawn.h"
#include "PurrInPerilEnemyPawn.h"
#include "PurrInPerilAsset.h"
#include "CustomComponents/PurrInPerilSmellDiscoverComponent.h"
#include "CustomComponents/PurrInPerilSmellProduceComponent.h"
#include "Subsystems/PurrInPerilSmellManagementSubsystem.h"

APurrInPerilMainPlayerState::APurrInPerilMainPlayerState(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;
}

void APurrInPerilMainPlayerState::BeginPlay()
{
    Super::BeginPlay();
    if (!bOverrideInitialPlayerStateParameter)
    {
        if (auto* GameplayNumericalSettings = UGameplayNumericalSettings::GetFromGameInstance(this))
        {
            InitialPlayerStateParameter = GameplayNumericalSettings->DefaultPlayerStateParameter;
        }
    }
    CurrentPlayerStateParameter = InitialPlayerStateParameter;
}

void APurrInPerilMainPlayerState::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    UWorld* World = GetWorld();
    if (World && !World->IsPaused())
    {
        if (APurrInPerilMainGameState* GameState = World->GetGameState<APurrInPerilMainGameState>())
        {
            if (!GameState->IsGameOver())
            {
                const FInLevelCostParameter& CostParameter = GameState->GetInLevelCostParameter();
                AddHungerValue(-CostParameter.HungerValueLostPerSecond * DeltaSeconds);

                if (APurrInPerilAnimalPawn* AnimalPawn = GetPawn<APurrInPerilAnimalPawn>())
                {
                    if (UPurrInPerilSmellManagementSubsystem* SmellManagementSubsystem = UPurrInPerilSmellManagementSubsystem::GetSubsystem(this))
                    {
                        const TSet<UPurrInPerilSmellProduceComponent*>& SmellProducers = SmellManagementSubsystem->GetAllSmellProducers();

                        float SanityValueDamagePerSecond = 0.0f;
                        for (const UPurrInPerilSmellProduceComponent* Producer : SmellProducers)
                        {
                            if (APurrInPerilEnemyPawn* EnemyPawn = Producer->GetOwner<APurrInPerilEnemyPawn>())
                            {
                                float Distance = (Producer->GetComponentLocation() - AnimalPawn->SmellDiscoverComponent->GetComponentLocation()).Length();
                                if (Distance < EnemyPawn->GetInLevelEnemyParameter().MaxDamagingDistance)
                                {
                                    SanityValueDamagePerSecond += EnemyPawn->GetInLevelEnemyParameter().SanityValueDamagePerEnemyPerSecond;
                                }
                            }
                        }
                        AddSanityValue(-SanityValueDamagePerSecond * DeltaSeconds);
                    }
                }
            }
        }
    }
}

bool APurrInPerilMainPlayerState::AddSanityValue(float AddValue)
{
    if (CurrentPlayerStateParameter.SanityValue <= 0 || CurrentPlayerStateParameter.SanityValue > InitialPlayerStateParameter.SanityValue)
    {
        return false;
    }
    CurrentPlayerStateParameter.SanityValue = FMath::Clamp(CurrentPlayerStateParameter.SanityValue + AddValue, 0, InitialPlayerStateParameter.SanityValue);
    return true;
}

bool APurrInPerilMainPlayerState::AddHungerValue(float AddValue)
{
    if (CurrentPlayerStateParameter.HungerValue <= 0 || CurrentPlayerStateParameter.HungerValue > InitialPlayerStateParameter.HungerValue)
    {
        return false;
    }
    CurrentPlayerStateParameter.HungerValue = FMath::Clamp(CurrentPlayerStateParameter.HungerValue + AddValue, 0, InitialPlayerStateParameter.HungerValue);
    return true;
}
