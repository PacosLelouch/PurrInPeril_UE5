// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PurrInPerilCommon.h"
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

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	bool bOverrideInitialPlayerStateParameter = false;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "PurrInPeril")
	FPlayerStateParameter InitialPlayerStateParameter;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	FPlayerStateParameter CurrentPlayerStateParameter;
};
