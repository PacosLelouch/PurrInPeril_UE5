// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilEnemyPawn.h"
#include "Components/BoxComponent.h"
#include "CustomComponents/PurrInPerilMovementComponent.h"
#include "CustomComponents/PurrInPerilHearingComponent.h"
#include "CustomComponents/PurrInPerilEnvironmentAudioComponent.h"
#include "PurrInPerilAsset.h"

APurrInPerilEnemyPawn::APurrInPerilEnemyPawn(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    SmellProduceComponent = CreateDefaultSubobject<UPurrInPerilSmellProduceComponent>(TEXT("SmellProduceComponent"));
    SmellProduceComponent->SetupAttachment(RootComponent);

    HearingComponent = CreateDefaultSubobject<UPurrInPerilHearingComponent>(TEXT("HearingComponent"));
    HearingComponent->SetupAttachment(RootComponent);

    VoiceComponent = CreateDefaultSubobject<UPurrInPerilEnvironmentAudioComponent>(TEXT("VoiceComponent"));
    VoiceComponent->SetupAttachment(RootComponent);
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
