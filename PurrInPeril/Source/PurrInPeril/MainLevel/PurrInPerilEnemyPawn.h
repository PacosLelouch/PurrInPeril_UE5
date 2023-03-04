// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PurrInPerilPawnBase.h"
#include "PurrInPerilEnemyPawn.generated.h"

class UBoxComponent;
class UPurrInPerilMovementComponent;

/**
* 
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API APurrInPerilEnemyPawn : public APurrInPerilPawnBase
{
	GENERATED_BODY()
public:
	APurrInPerilEnemyPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};