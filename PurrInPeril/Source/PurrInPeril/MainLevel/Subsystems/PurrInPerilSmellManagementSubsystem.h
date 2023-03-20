// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Subsystems/WorldSubsystem.h"
#include "PurrInPerilSmellManagementSubsystem.generated.h"

class UPurrInPerilSmellProduceComponent;

/**
* 
*/
UCLASS(BlueprintType)
class PURRINPERIL_API UPurrInPerilSmellManagementSubsystem : public UWorldSubsystem // UTickableWorldSubsystem
{
	GENERATED_BODY()
public:
	static UPurrInPerilSmellManagementSubsystem* GetSubsystem(UObject* WorldContextObject);

	UPurrInPerilSmellManagementSubsystem();

	virtual bool ShouldCreateSubsystem(UObject* Outer) const override;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Smell")
	void RegisterSmellProducer(UPurrInPerilSmellProduceComponent* SmellProducer);

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Smell")
	void UnregisterSmellProducer(UPurrInPerilSmellProduceComponent* SmellProducer);

	// Return the closest.
	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Smell")
	UPurrInPerilSmellProduceComponent* GetSmellProducersInDistance(
		TMap<UPurrInPerilSmellProduceComponent*, float>& OutSmellProducers, 
		USceneComponent* OriginSceneComponent, float MaxDistanceReturn, float MaxDistanceMap, 
		bool bNeedMap = false, bool bWithNoSmell = false, bool bWithOrigin = false);

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Smell")
	const TSet<UPurrInPerilSmellProduceComponent*>& GetAllSmellProducers() const { return SmellProducers; }

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, BlueprintGetter = "GetAllSmellProducers", Category = "PurrInPeril|Smell")
	TSet<UPurrInPerilSmellProduceComponent*> SmellProducers;
};