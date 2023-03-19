// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilAudioManagementSubsystem.h"
#include "CustomComponents/PurrInPerilEnvironmentAudioComponent.h"
#include "PurrInPerilMainGameState.h"
#include "Engine/World.h"
#include "Math/Transform.h"

UPurrInPerilAudioManagementSubsystem* UPurrInPerilAudioManagementSubsystem::GetSubsystem(UObject* WorldContextObject)
{
    UWorld* World = WorldContextObject->GetWorld();
    if (World)
    {
        UPurrInPerilAudioManagementSubsystem* Subsys = World->GetSubsystem<UPurrInPerilAudioManagementSubsystem>();
        return Subsys;
    }
    return nullptr;
}

UPurrInPerilAudioManagementSubsystem::UPurrInPerilAudioManagementSubsystem()
    : Super()
{

}

bool UPurrInPerilAudioManagementSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
    if (!Super::ShouldCreateSubsystem(Outer))
    {
        return false;
    }

    // Cannot use GetWorld() and get GameState before initialization!
    UWorld* World = Cast<UWorld>(Outer);
    //APurrInPerilMainGameState* GameState = World->GetGameState<APurrInPerilMainGameState>();
    //if (!GameState)
    //{
    //    return false;
    //}

    return true;
}

void UPurrInPerilAudioManagementSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);
    AudioComponents.Empty();
}

void UPurrInPerilAudioManagementSubsystem::Deinitialize()
{
    AudioComponents.Empty();
    Super::Deinitialize();
}

void UPurrInPerilAudioManagementSubsystem::RegisterAudioComponent(UPurrInPerilEnvironmentAudioComponent* AudioComponent)
{
    AudioComponents.Add(AudioComponent);
}

void UPurrInPerilAudioManagementSubsystem::UnregisterAudioComponent(UPurrInPerilEnvironmentAudioComponent* AudioComponent)
{
    AudioComponents.Remove(AudioComponent);
}
