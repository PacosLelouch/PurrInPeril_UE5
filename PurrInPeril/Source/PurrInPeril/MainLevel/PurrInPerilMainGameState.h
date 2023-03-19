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

	UFUNCTION(BlueprintGetter, Category = "PurrInPeril")
	const FInLevelCostParameter& GetInLevelCostParameter() const { return InLevelCostParameter; }

	UFUNCTION(BlueprintGetter, Category = "PurrInPeril")
	const FInLevelTimeParameter& GetInLevelTimeParameter() const { return InLevelTimeParameter; }

	UFUNCTION(BlueprintGetter, Category = "PurrInPeril")
	float GetCurrentCountdownInSecond() const { return CurrentCountdownInSecond; }

	UFUNCTION(BlueprintSetter, Category = "PurrInPeril")
	void SetIsGameOver(const bool bValue);

	UFUNCTION(BlueprintGetter, Category = "PurrInPeril")
	bool IsGameOver() const { return bIsGameOver; }

protected:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, BlueprintGetter = "IsGameOver", BlueprintSetter = "SetIsGameOver", Category = "PurrInPeril")
	bool bIsGameOver = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril")
	bool bOverrideInLevelCostParameter = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, BlueprintGetter = "GetInLevelCostParameter", Category = "PurrInPeril")
	FInLevelCostParameter InLevelCostParameter;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril")
	bool bOverrideInLevelTimeParameter = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, BlueprintGetter = "GetInLevelTimeParameter", Category = "PurrInPeril")
	FInLevelTimeParameter InLevelTimeParameter;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, BlueprintGetter = "GetCurrentCountdownInSecond", Category = "PurrInPeril")
	float CurrentCountdownInSecond = 180.0f;
};
