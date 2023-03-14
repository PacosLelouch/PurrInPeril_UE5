// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilCatFoodActor.h"
#include "PurrInPerilMainPlayerController.h"
#include "PurrInPerilMainPlayerState.h"
#include "PurrInPerilAsset.h"


APurrInPerilCatFoodActor::APurrInPerilCatFoodActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
}

void APurrInPerilCatFoodActor::BeginPlay()
{
	Super::BeginPlay();
    if (auto* GameplayNumericalSettings = UGameplayNumericalSettings::GetFromGameInstance(this))
    {
        if (!bOverrideDurability)
        {
            Durability = GameplayNumericalSettings->DefaultInLevelCostParameter.CatFoodDurability;
        }
        if (!bOverrideRecoveryHungerValue)
        {
            RecoveryHungerValue = GameplayNumericalSettings->DefaultInLevelCostParameter.CatFoodRecoveryHungerValue;
        }
    }
}

void APurrInPerilCatFoodActor::OpenInteraction_Implementation(AController* Controller)
{
	Super::OpenInteraction_Implementation(Controller);
    APurrInPerilMainPlayerState* PlayerState = Controller->GetPlayerState<APurrInPerilMainPlayerState>();
    if (PlayerState)
    {
        PlayerState->AddHungerValue(RecoveryHungerValue);
    }
}

void APurrInPerilCatFoodActor::CloseInteraction_Implementation(AController* Controller)
{
	Super::CloseInteraction_Implementation(Controller);
}