// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PurrInPerilPawnBase.h"
#include "PurrInPerilAnimalPawn.generated.h"

class UBoxComponent;
class UPurrInPerilMovementComponent;
class UPurrInPerilSmellDiscoverComponent;

/**
* 
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API APurrInPerilAnimalPawn : public APurrInPerilPawnBase
{
	GENERATED_BODY()
public:
	APurrInPerilAnimalPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril")
	UPurrInPerilSmellDiscoverComponent* SmellDiscoverComponent = nullptr;
};