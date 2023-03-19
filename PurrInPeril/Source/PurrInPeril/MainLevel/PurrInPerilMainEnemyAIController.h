// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PurrInPerilMainEnemyAIController.generated.h"

class APurrInPerilTaskActorBase;
class UPurrInPerilEnvironmentAudioComponent;

/**
* 
*/
UCLASS(Blueprintable)
class PURRINPERIL_API APurrInPerilMainEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	APurrInPerilMainEnemyAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// A callback that perceives the player completing a task.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PurrInPeril|Task")
	void OnPlayerCompletePartOfTask(APurrInPerilTaskActorBase* TaskActor, AController* Controller);

	// A callback that receives audio emitting event.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PurrInPeril|Task")
	void OnSoundEmitted(UPurrInPerilEnvironmentAudioComponent* AudioEmitted);
};