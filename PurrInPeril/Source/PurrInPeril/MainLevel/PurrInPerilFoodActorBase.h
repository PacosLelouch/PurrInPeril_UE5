// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "CustomComponents/PurrInPerilInteractableComponent.h"
#include "CustomComponents/PurrInPerilSmellProduceComponent.h"
#include "PurrInPerilFoodActorBase.generated.h"

class UPrimitiveComponent;
class UUserWidget;
class UWidgetComponent;
class APurrInPerilMainPlayerController;

/**
*
*/
UCLASS(Abstract, BlueprintType, Blueprintable)
class PURRINPERIL_API APurrInPerilFoodActorBase : public AActor, public IInteractableActorInterface, public ISmellProducerInterface
{
	GENERATED_BODY()
public:
	APurrInPerilFoodActorBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//~ Begin IInteractableActorInterface.
	virtual UPurrInPerilInteractableComponent* GetInteractableComponent_Implementation() override;
	//~ End IInteractableActorInterface.

	//~ Begin ISmellProducerInterface.
	virtual UPurrInPerilSmellProduceComponent* GetSmellProduceComponent_Implementation() override;
	//~ End ISmellProducerInterface.

	//~ Begin interaction.
	//~ Begin IInteractableActorInterface.
	virtual void OpenInteraction_Implementation(AController* Controller) override;

	virtual void CloseInteraction_Implementation(AController* Controller) override;
	//~ End IInteractableActorInterface.
	//~ End interaction.

	//~ Begin FoodActorBase.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PurrInPeril")
	void OnFoodInteractWithPlayer(AController* Controller, bool bSucceeded);
	//~ End FoodActorBase.

	UFUNCTION(BlueprintPure, Category = "PurrInPeril")
	bool IsColdDownCompleted() const;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril")
	UPurrInPerilInteractableComponent* InteractableComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril")
	UPurrInPerilSmellProduceComponent* SmellProduceComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril")
	bool bOverrideDurability = false;

	// Durability means how many times of interaction to destroy itself. Set to -1 for no destroy.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril")
	int32 Durability = -1;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril")
	bool bOverrideInteractColdDown = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril")
	float MaxInteractColdDownInSecond = 0.0f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril")
	float CurrentInteractColdDownInSecond = 0.0f;
};
