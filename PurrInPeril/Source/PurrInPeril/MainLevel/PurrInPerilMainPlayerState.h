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

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintGetter, Category = "PurrInPeril")
	const FPlayerStateParameter& GetInitialPlayerStateParameter() const { return InitialPlayerStateParameter; }

	UFUNCTION(BlueprintGetter, Category = "PurrInPeril")
	const FPlayerStateParameter& GetCurrentPlayerStateParameter() const { return CurrentPlayerStateParameter; }

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	bool AddSanityValue(float AddValue);

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	bool AddHungerValue(float AddValue);

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril")
	bool bOverrideInitialPlayerStateParameter = false;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, BlueprintGetter = "GetInitialPlayerStateParameter", Category = "PurrInPeril")
	FPlayerStateParameter InitialPlayerStateParameter;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, BlueprintGetter = "GetCurrentPlayerStateParameter", Category = "PurrInPeril")
	FPlayerStateParameter CurrentPlayerStateParameter;
};
