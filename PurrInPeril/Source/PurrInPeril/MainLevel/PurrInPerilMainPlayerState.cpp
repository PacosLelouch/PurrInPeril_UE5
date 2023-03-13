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
