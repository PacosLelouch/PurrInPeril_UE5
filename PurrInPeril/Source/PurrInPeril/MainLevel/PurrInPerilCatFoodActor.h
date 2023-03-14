// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "PurrInPerilFoodActorBase.h"
#include "PurrInPerilCatFoodActor.generated.h"

/**
*
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API APurrInPerilCatFoodActor : public APurrInPerilFoodActorBase
{
	GENERATED_BODY()
public:
	APurrInPerilCatFoodActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	//~ Begin interaction.
	//~ Begin IInteractableActorInterface.
	virtual void OpenInteraction_Implementation(AController* Controller) override;

	virtual void CloseInteraction_Implementation(AController* Controller) override;
	//~ End IInteractableActorInterface.
	//~ End interaction.

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril")
	bool bOverrideRecoveryHungerValue = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril")
	float RecoveryHungerValue = 20.0f;
};