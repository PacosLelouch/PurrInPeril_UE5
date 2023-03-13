// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PurrInPerilCommon.h"
#include "PurrInPerilMainGameState.generated.h"

/**
* 
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API APurrInPerilMainGameState : public AGameStateBase
{
	GENERATED_BODY()
public:
	APurrInPerilMainGameState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	bool bOverrideInLevelCostParameter = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	FInLevelCostParameter InLevelCostParameter;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	bool bOverrideInLevelTimeParameter = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	FInLevelTimeParameter InLevelTimeParameter;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril")
	float CurrentCountdownInSecond = 180.0f;
};
