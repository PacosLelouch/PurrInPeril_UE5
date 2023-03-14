// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilMainPlayerState.h"
#include "PurrInPerilAsset.h"

APurrInPerilMainPlayerState::APurrInPerilMainPlayerState(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

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

bool APurrInPerilMainPlayerState::AddSanityValue(float AddValue)
{
    if (CurrentPlayerStateParameter.SanityValue <= 0 || CurrentPlayerStateParameter.SanityValue >= InitialPlayerStateParameter.SanityValue)
    {
        return false;
    }
    CurrentPlayerStateParameter.SanityValue = FMath::Clamp(CurrentPlayerStateParameter.SanityValue + AddValue, 0, InitialPlayerStateParameter.SanityValue);
    return true;
}

bool APurrInPerilMainPlayerState::AddHungerValue(float AddValue)
{
    if (CurrentPlayerStateParameter.HungerValue <= 0 || CurrentPlayerStateParameter.HungerValue >= InitialPlayerStateParameter.HungerValue)
    {
        return false;
    }
    CurrentPlayerStateParameter.HungerValue = FMath::Clamp(CurrentPlayerStateParameter.HungerValue + AddValue, 0, InitialPlayerStateParameter.HungerValue);
    return true;
}
