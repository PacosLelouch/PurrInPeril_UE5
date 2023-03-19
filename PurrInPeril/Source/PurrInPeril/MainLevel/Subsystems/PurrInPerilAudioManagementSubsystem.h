// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Subsystems/WorldSubsystem.h"
#include "PurrInPerilAudioManagementSubsystem.generated.h"

class UPurrInPerilEnvironmentAudioComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSoundEmittedDynamicDelegate, UPurrInPerilEnvironmentAudioComponent*, EmittedComponent);

/**
*
*/
UCLASS(BlueprintType)
class PURRINPERIL_API UPurrInPerilAudioManagementSubsystem : public UWorldSubsystem // UTickableWorldSubsystem
{
	GENERATED_BODY()
public:
	static UPurrInPerilAudioManagementSubsystem* GetSubsystem(UObject* WorldContextObject);

	UPurrInPerilAudioManagementSubsystem();

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Audio")
	void RegisterAudioComponent(UPurrInPerilEnvironmentAudioComponent* SmellProducer);

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Audio")
	void UnregisterAudioComponent(UPurrInPerilEnvironmentAudioComponent* SmellProducer);

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Audio")
	const TSet<UPurrInPerilEnvironmentAudioComponent*>& GetAllAudioComponents() const { return AudioComponents; }

	UPROPERTY(BlueprintAssignable, Category = "PurrInPeril|Audio")
	FOnSoundEmittedDynamicDelegate OnSoundEmitted;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, BlueprintGetter = "GetAllAudioComponents", Category = "PurrInPeril|Audio")
	TSet<UPurrInPerilEnvironmentAudioComponent*> AudioComponents;
};