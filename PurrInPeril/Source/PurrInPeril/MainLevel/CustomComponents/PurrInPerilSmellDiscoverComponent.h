// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PurrInPerilCommon.h"
#include "PurrInPerilSmellDiscoverComponent.generated.h"

class UPurrInPerilSmellProduceComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAccurateSmellBeginDynamicDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAccurateSmellEndDynamicDelegate);

/**
* 
*/
UCLASS(ClassGroup = ("Smell", "PurrInPeril"), BlueprintType, Blueprintable, meta = (BlueprintSpawnableComponent))
class PURRINPERIL_API UPurrInPerilSmellDiscoverComponent : public USceneComponent
{
	GENERATED_BODY()
public:
	UPurrInPerilSmellDiscoverComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	void ActivateAccurateSmell(float Time);

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	void ResetSmellDistanceParameter();

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	void AddMaxSmellDistance(float AddValue);


	UPROPERTY(BlueprintReadOnly, Category = "PurrInPeril")
	bool bIsActivatingAccurateSmell = false;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "PurrInPeril")
	bool bOverrideSmellDistanceParameter = false;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "PurrInPeril")
	FSmellDistanceParameter InitialSmellDistanceParameter;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril")
	FSmellDistanceParameter SmellDistanceParameter;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril")
	TMap<UPurrInPerilSmellProduceComponent*, float> PerceivedSmellProducers;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril")
	UPurrInPerilSmellProduceComponent* PerceivedNearestSmellProducer = nullptr;

	UPROPERTY(BlueprintAssignable, BlueprintReadOnly, Category = "PurrInPeril")
	FOnAccurateSmellBeginDynamicDelegate OnAccurateSmellBegin;

	UPROPERTY(BlueprintAssignable, BlueprintReadOnly, Category = "PurrInPeril")
	FOnAccurateSmellEndDynamicDelegate OnAccurateSmellEnd;

	FTimerHandle AccurateTimerHandle;
};
