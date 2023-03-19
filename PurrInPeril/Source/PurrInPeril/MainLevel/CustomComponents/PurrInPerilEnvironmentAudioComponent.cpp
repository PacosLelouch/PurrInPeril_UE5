// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilEnvironmentAudioComponent.h"
#include "PurrInPerilAsset.h"
#include "Subsystems/PurrInPerilAudioManagementSubsystem.h"

UPurrInPerilEnvironmentAudioComponent::UPurrInPerilEnvironmentAudioComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bAllowSpatialization = true;
}

void UPurrInPerilEnvironmentAudioComponent::BeginPlay()
{
	Super::BeginPlay();
	OnAudioPlayStateChanged.AddDynamic(this, &UPurrInPerilEnvironmentAudioComponent::OnPlayAudio);
	if (UPurrInPerilAudioManagementSubsystem* AudioManagementSubsystem = UPurrInPerilAudioManagementSubsystem::GetSubsystem(this))
	{
		AudioManagementSubsystem->RegisterAudioComponent(this);
	}
	if (auto* GameplayAudioSettings = UGameplayAudioSettings::GetFromGameInstance(this))
	{
		if (!AttenuationSettings)
		{
			AttenuationSettings = GameplayAudioSettings->InLevelAudioSettings.DefaultEnvironmentSoundAttenuation;
		}
		if (!SoundClassOverride)
		{
			SoundClassOverride = GameplayAudioSettings->InLevelAudioSettings.DefaultEnvironmentSoundClass;
		}
	}
}

void UPurrInPerilEnvironmentAudioComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (UPurrInPerilAudioManagementSubsystem* AudioManagementSubsystem = UPurrInPerilAudioManagementSubsystem::GetSubsystem(this))
	{
		AudioManagementSubsystem->UnregisterAudioComponent(this);
	}
	OnAudioPlayStateChanged.RemoveDynamic(this, &UPurrInPerilEnvironmentAudioComponent::OnPlayAudio);
	Super::EndPlay(EndPlayReason);
}

void UPurrInPerilEnvironmentAudioComponent::OnPlayAudio_Implementation(EAudioComponentPlayState PlayState)
{
	if (PlayState == EAudioComponentPlayState::Playing)
	{
		if (UPurrInPerilAudioManagementSubsystem* AudioManagementSubsystem = UPurrInPerilAudioManagementSubsystem::GetSubsystem(this))
		{
			AudioManagementSubsystem->OnSoundEmitted.Broadcast(this);
		}
	}
}
