// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilCatMintActor.h"
#include "PurrInPerilMainPlayerController.h"
#include "PurrInPerilMainPlayerState.h"
#include "PurrInPerilAsset.h"


APurrInPerilCatMintActor::APurrInPerilCatMintActor(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{

}

void APurrInPerilCatMintActor::BeginPlay()
{
    Super::BeginPlay();
    if (auto* GameplayNumericalSettings = UGameplayNumericalSettings::GetFromGameInstance(this))
    {
        if (!bOverrideDurability)
        {
            Durability = GameplayNumericalSettings->DefaultInLevelCostParameter.CatMintDurability;
        }
        if (!bOverrideRecoverySanityValue)
        {
            RecoverySanityValue = GameplayNumericalSettings->DefaultInLevelCostParameter.CatMintRecoverySanityValue;
        }
    }
}

void APurrInPerilCatMintActor::OpenInteraction_Implementation(AController* Controller)
{
    Super::OpenInteraction_Implementation(Controller);
    APurrInPerilMainPlayerState* PlayerState = Controller->GetPlayerState<APurrInPerilMainPlayerState>();
    if (PlayerState)
    {
        PlayerState->AddSanityValue(RecoverySanityValue);
    }
}

void APurrInPerilCatMintActor::CloseInteraction_Implementation(AController* Controller)
{
    Super::CloseInteraction_Implementation(Controller);
}