// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Subsystems/WorldSubsystem.h"
#include "CustomComponents/PurrInPerilSmellProduceComponent.h"
#include "PurrInPerilSmellManagementSubsystem.generated.h"


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

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	void RegisterSmellProducer(UPurrInPerilSmellProduceComponent* SmellProducer);

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	void UnregisterSmellProducer(UPurrInPerilSmellProduceComponent* SmellProducer);

	// Return the closest.
	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	UPurrInPerilSmellProduceComponent* GetSmellProducersInDistance(
		TMap<UPurrInPerilSmellProduceComponent*, float>& OutSmellProducers, 
		USceneComponent* OriginSceneComponent, float MaxDistance, 
		bool bNeedMap = false, bool bWithNoSmell = false, bool bWithOrigin = false);

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril")
	TSet<UPurrInPerilSmellProduceComponent*> SmellProducers;
};