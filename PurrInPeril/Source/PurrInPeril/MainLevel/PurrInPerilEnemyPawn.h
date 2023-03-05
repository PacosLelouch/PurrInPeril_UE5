// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PurrInPerilPawnBase.h"
#include "CustomComponents/PurrInPerilSmellProduceComponent.h"
#include "PurrInPerilEnemyPawn.generated.h"

class UBoxComponent;
class UPurrInPerilMovementComponent;

/**
* 
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API APurrInPerilEnemyPawn : public APurrInPerilPawnBase, public ISmellProducerInterface
{
	GENERATED_BODY()
public:
	APurrInPerilEnemyPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~ Begin ISmellProducerInterface override.
	virtual UPurrInPerilSmellProduceComponent* GetSmellProduceComponent_Implementation() override;
	//~ End ISmellProducerInterface override.

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril")
	UPurrInPerilSmellProduceComponent* SmellProduceComponent = nullptr;
};