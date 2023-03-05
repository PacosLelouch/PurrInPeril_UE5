// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PurrInPerilMainPlayerState.generated.h"

/**
* 
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API APurrInPerilMainPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	APurrInPerilMainPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	float SanityValue = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	float HungerValue = 100.0f;
};
