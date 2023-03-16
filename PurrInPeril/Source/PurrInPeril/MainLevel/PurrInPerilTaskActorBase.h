// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "PurrInPerilGlobalDefines.h"
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

	UFUNCTION(BlueprintImplementableEvent, Category = "PurrInPeril|Task", meta = (DisplayName = "Complete This Part Of Task Blueprint Implementation"))
	void BP_CompleteThisPartOfTask(AController* Controller);

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Task")
	void ResetThisPartOfTask(AController* Controller);

	virtual void ResetThisPartOfTask_Implementation(AController* Controller);

	UFUNCTION(BlueprintImplementableEvent, Category = "PurrInPeril|Task", meta = (DisplayName = "Reset This Part Of Task Blueprint Implementation"))
	void BP_ResetThisPartOfTask(AController* Controller);


	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Task")
	bool IsThisPartOfTaskCompleted(AController* Controller) const;
	//~ End task.

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril")
	UPurrInPerilInteractableComponent* InteractableComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril")
	UPurrInPerilSmellProduceComponent* SmellProduceComponent = nullptr;

#if TASK_COUNTED_PER_PLAYER
	TMap<AController*, bool> PlayerToPartOfTaskCompleted;
#else // !TASK_COUNTED_PER_PLAYER
	bool bIsTaskCompleted = false;
#endif // TASK_COUNTED_PER_PLAYER

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere, Category = "PurrInPeril|Task")
	bool bIsTaskCompleted_Debugging = false;

	void Sync_IsTaskCompleted_Debugging(AController* Controller);
#endif // WITH_EDITORONLY_DATA
};
