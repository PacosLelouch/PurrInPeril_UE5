// Copyright Epic Games, Inc. All Rights Reserved.


#include "PurrInPerilMainEnemyAIController.h"
#include "Subsystems/PurrInPerilTaskManagementSubsystem.h"
#include "Subsystems/PurrInPerilSmellManagementSubsystem.h"
#include "Subsystems/PurrInPerilAudioManagementSubsystem.h"
#include "CustomComponents/PurrInPerilEnvironmentAudioComponent.h"

APurrInPerilMainEnemyAIController::APurrInPerilMainEnemyAIController(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    bWantsPlayerState = false;
}

void APurrInPerilMainEnemyAIController::BeginPlay()
{
    Super::BeginPlay();
    if (UPurrInPerilTaskManagementSubsystem* TaskManagementSubsystem = UPurrInPerilTaskManagementSubsystem::GetSubsystem(this))
    {
        TaskManagementSubsystem->OnPartOfTaskComplete.AddDynamic(this, &APurrInPerilMainEnemyAIController::OnPlayerCompletePartOfTask);
    }
    if (UPurrInPerilAudioManagementSubsystem* AudioManagementSubsystem = UPurrInPerilAudioManagementSubsystem::GetSubsystem(this))
    {
        AudioManagementSubsystem->OnSoundEmitted.AddDynamic(this, &APurrInPerilMainEnemyAIController::OnSoundEmitted);
    }
}

void APurrInPerilMainEnemyAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (UPurrInPerilAudioManagementSubsystem* AudioManagementSubsystem = UPurrInPerilAudioManagementSubsystem::GetSubsystem(this))
    {
        AudioManagementSubsystem->OnSoundEmitted.RemoveDynamic(this, &APurrInPerilMainEnemyAIController::OnSoundEmitted);
    }
    if (UPurrInPerilTaskManagementSubsystem* TaskManagementSubsystem = UPurrInPerilTaskManagementSubsystem::GetSubsystem(this))
    {
        TaskManagementSubsystem->OnPartOfTaskComplete.RemoveDynamic(this, &APurrInPerilMainEnemyAIController::OnPlayerCompletePartOfTask);
    }
    Super::EndPlay(EndPlayReason);
}

void APurrInPerilMainEnemyAIController::OnPlayerCompletePartOfTask_Implementation(APurrInPerilTaskActorBase* TaskActor, AController* Controller)
{
}

void APurrInPerilMainEnemyAIController::OnSoundEmitted_Implementation(UPurrInPerilEnvironmentAudioComponent* AudioEmitted)
{
}
