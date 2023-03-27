// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Subsystems/WorldSubsystem.h"
#include "PurrInPerilAsset.h"
#include "Math/IntPoint.h"
#include "PurrInPerilTaskManagementSubsystem.generated.h"

class AController;
class APurrInPerilTaskActorBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPartOfTaskCompleteByPlayerDynamicDelegate, APurrInPerilTaskActorBase*, TaskActor, AController*, Controller);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPartOfTaskResetByPlayerDynamicDelegate, APurrInPerilTaskActorBase*, TaskActor, AController*, Controller);

USTRUCT(BlueprintType)
struct PURRINPERIL_API FPurrInPerilTaskActorSet
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril|Task")
	TSet<APurrInPerilTaskActorBase*> Set;
};

USTRUCT(BlueprintType)
struct PURRINPERIL_API FPurrInPerilTaskNum
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril|Task")
	int32 TaskNum = 0;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril|Task")
	int32 TaskCompleteNum = 0;
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
	FPurrInPerilTaskNum GetTaskNumAndCompleteCount(const FPurrInPerilTaskIdentifier& TaskIdentifier, AController* Controller) const;

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Task", meta = (AutoCreateRefTerm = "IgnoringTasks"))
	int32 GetRemainingTaskIdentifierNotCompleted(TSet<FPurrInPerilTaskIdentifier>& OutRemainingTasks, const TSet<FPurrInPerilTaskIdentifier>& IgnoringTasks, AController* Controller) const;


	UPROPERTY(BlueprintAssignable, Category = "PurrInPeril|Task")
	FOnPartOfTaskCompleteByPlayerDynamicDelegate OnPartOfTaskComplete;

	UPROPERTY(BlueprintAssignable, Category = "PurrInPeril|Task")
	FOnPartOfTaskResetByPlayerDynamicDelegate OnPartOfTaskReset;

protected:
	// Is it useful?
	void InitializeTaskActorsFromWorld();

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril|Task")
	TMap<FPurrInPerilTaskIdentifier, FPurrInPerilTaskActorSet> TaskActors;
};