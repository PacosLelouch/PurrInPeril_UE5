// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "PurrInPerilEnvironmentAudioComponent.generated.h"

class UPurrInPerilEnvironmentAudioComponent;

/**
*
*/
UCLASS(ClassGroup = ("Audio", "PurrInPeril"), BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class PURRINPERIL_API UPurrInPerilEnvironmentAudioComponent : public UAudioComponent
{
	GENERATED_BODY()
public:
	UPurrInPerilEnvironmentAudioComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Audio")
	FName AudioTag = TEXT("EnvironmentAudio");

protected:
	UFUNCTION(BlueprintNativeEvent, Category = "PurrInPeril|Audio")
	void OnPlayAudio(EAudioComponentPlayState PlayState);
};