// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PurrInPerilSmellDiscoverComponent.generated.h"

class UPurrInPerilSmellProduceComponent;

/**
* 
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UPurrInPerilSmellDiscoverComponent : public USceneComponent
{
	GENERATED_BODY()
public:
	UPurrInPerilSmellDiscoverComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	virtual void EndPlay(EEndPlayReason::Type EndPlayReason) override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	void ActivateAccurateSmell(float Time);

	UPROPERTY(BlueprintReadOnly, Category = "PurrInPeril")
	bool bIsActivatingAccurateSmell = false;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "PurrInPeril")
	float MaxSmellDistance = 200.0f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "PurrInPeril")
	float MinSmellDistance = 20.0f;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril")
	TMap<UPurrInPerilSmellProduceComponent*, float> PerceivedSmellProducers;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril")
	UPurrInPerilSmellProduceComponent* PerceivedNearestSmellProducer = nullptr;

	FTimerHandle AccurateTimerHandle;
};
