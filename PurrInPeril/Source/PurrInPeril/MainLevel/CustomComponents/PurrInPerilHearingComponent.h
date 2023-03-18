// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "UObject/Interface.h"
#include "Sound/SoundAttenuation.h"
#include "PurrInPerilHearingComponent.generated.h"

class UPurrInPerilEnvironmentAudioComponent;
class UPurrInPerilHearingComponent;
class UPurrInPerilPlayerHearingComponent;

/**
*
*/
UCLASS(ClassGroup = ("Audio", "PurrInPeril"), BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class PURRINPERIL_API UPurrInPerilHearingComponent : public USceneComponent
{
	GENERATED_BODY()
public:
	UPurrInPerilHearingComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
};

/**
*
*/
UCLASS(ClassGroup = ("Audio", "PurrInPeril"), BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class PURRINPERIL_API UPurrInPerilPlayerHearingComponent : public UPurrInPerilHearingComponent
{
	GENERATED_BODY()
public:
	UPurrInPerilPlayerHearingComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Is it useful? How to customize the hearing of the player?
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril|Audio")
	FSoundAttenuationSettings SoundAttenuationSettings;
};