// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "CustomComponents/PurrInPerilInteractableComponent.h"
#include "CustomComponents/PurrInPerilSmellProduceComponent.h"
#include "PurrInPerilTaskActorBase.generated.h"

class UPrimitiveComponent;
class UUserWidget;
class UWidgetComponent;
class APurrInPerilMainPlayerController;

/**
* 
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API APurrInPerilTaskActorBase : public AActor, public IInteractableActorInterface, public ISmellProducerInterface
{
	GENERATED_BODY()
public:
	APurrInPerilTaskActorBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	//~ Begin IInteractableActorInterface.
	virtual UPurrInPerilInteractableComponent* GetInteractableComponent_Implementation() override;
	//~ End IInteractableActorInterface.

	//~ Begin ISmellProducerInterface.
	virtual UPurrInPerilSmellProduceComponent* GetSmellProduceComponent_Implementation() override;
	//~ End ISmellProducerInterface.


	//~ Begin task.
	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Task")
	void CompleteThisPartOfTask(AController* Controller);

	virtual void CompleteThisPartOfTask_Implementation(AController* Controller);

	UFUNCTION(BlueprintImplementableEvent, Category = "PurrInPeril|Task")
	void BP_CompleteThisPartOfTask(AController* Controller);

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Task")
	void ResetThisPartOfTask(AController* Controller);

	virtual void ResetThisPartOfTask_Implementation(AController* Controller);

	UFUNCTION(BlueprintImplementableEvent, Category = "PurrInPeril|Task")
	void BP_ResetThisPartOfTask(AController* Controller);


	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Task")
	bool IsThisPartOfTaskCompleted(AController* Controller) const;
	//~ End task.

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril")
	UPurrInPerilInteractableComponent* InteractableComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril")
	UPurrInPerilSmellProduceComponent* SmellProduceComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril|Task")
	TMap<AController*, bool> PlayerToPartOfTaskCompleted;
};
