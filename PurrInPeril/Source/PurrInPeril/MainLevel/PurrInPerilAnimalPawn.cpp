// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilAnimalPawn.h"
#include "Components/BoxComponent.h"
#include "CustomComponents/PurrInPerilMovementComponent.h"
#include "CustomComponents/PurrInPerilSmellDiscoverComponent.h"
#include "CustomComponents/PurrInPerilHearingComponent.h"

APurrInPerilAnimalPawn::APurrInPerilAnimalPawn(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    //PrimaryActorTick.bCanEverTick = true;

    BoxCollider->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);

    SmellDiscoverComponent = CreateDefaultSubobject<UPurrInPerilSmellDiscoverComponent>(TEXT("SmellDiscoverComponent"));
    SmellDiscoverComponent->SetupAttachment(RootComponent);

    PlayerHearingComponent = CreateDefaultSubobject<UPurrInPerilPlayerHearingComponent>(TEXT("PlayerHearingComponent"));
    PlayerHearingComponent->SetupAttachment(RootComponent);
}