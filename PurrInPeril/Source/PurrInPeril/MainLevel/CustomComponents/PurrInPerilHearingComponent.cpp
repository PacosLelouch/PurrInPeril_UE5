// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilHearingComponent.h"
#include "PurrInPerilEnvironmentAudioComponent.h"
#include "Subsystems/PurrInPerilAudioManagementSubsystem.h"

UPurrInPerilHearingComponent::UPurrInPerilHearingComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UPurrInPerilHearingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPurrInPerilHearingComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

UPurrInPerilPlayerHearingComponent::UPurrInPerilPlayerHearingComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SoundAttenuationSettings.DistanceAlgorithm = EAttenuationDistanceModel::NaturalSound;
	SoundAttenuationSettings.bAttenuate = true;
	SoundAttenuationSettings.bSpatialize = true;
}

void UPurrInPerilPlayerHearingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPurrInPerilPlayerHearingComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}
