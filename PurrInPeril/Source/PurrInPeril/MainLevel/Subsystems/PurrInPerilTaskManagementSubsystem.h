// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Subsystems/WorldSubsystem.h"
#include "PurrInPerilTaskActorBase.h"
#include "PurrInPerilAsset.h"
#include "Math/IntPoint.h"
#include "PurrInPerilTaskManagementSubsystem.generated.h"

USTRUCT(BlueprintType)
struct PURRINPERIL_API FPurrInPerilTaskActorSet
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril|Task")
	TSet<APurrInPerilTaskActorBase*> Set;
};

/**
* 
*/
UCLASS(BlueprintType)
class PURRINPERIL_API UPurrInPerilTaskManagementSubsystem : public UWorldSubsystem // UTickableWorldSubsystem
{
	GENERATED_BODY()
public:
	static UPurrInPerilTaskManagementSubsystem* GetSubsystem(UObject* WorldContextObject);

	UPurrInPerilTaskManagementSubsystem();

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Task")
	void RegisterTaskActor(APurrInPerilTaskActorBase* TaskActor);

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Task")
	void UnregisterTaskActor(APurrInPerilTaskActorBase* TaskActor);

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Task")
	bool GetTaskIdentifier(APurrInPerilTaskActorBase* TaskActor, FPurrInPerilTaskIdentifier& OutTaskIdentifier) const;

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Task")
	FIntPoint GetTaskNumAndCompleteCount(const FPurrInPerilTaskIdentifier& TaskIdentifier, AController* Controller) const;

protected:
	// Is it useful?
	void InitializeTaskActorsFromWorld();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril|Task")
	TMap<FPurrInPerilTaskIdentifier, FPurrInPerilTaskActorSet> TaskActors;
};