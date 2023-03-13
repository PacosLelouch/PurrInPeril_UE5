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

	//~ Begin overlap.
	// declare overlap begin function.
	UFUNCTION()
	void OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
	//void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// declare overlap end function.
	UFUNCTION()
	void OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);
	//void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// C++ implemented overlap begin function.
	virtual void OnOverlapBegin_Implementation(AActor* OverlappedActor, AActor* OtherActor);
	//virtual void OnOverlapBegin_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// C++ implemented overlap end function.
	virtual void OnOverlapEnd_Implementation(AActor* OverlappedActor, AActor* OtherActor);
	//virtual void OnOverlapEnd_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// BP implemented overlap begin function.
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);
	//void BP_OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// BP implemented overlap end function.
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);
	//void BP_OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	//~ End overlap.

	//~ Begin interaction.
	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Widget")
	void OpenInteraction(AController* Controller);

	virtual void OpenInteraction_Implementation(AController* Controller);

	UFUNCTION(BlueprintImplementableEvent, Category = "PurrInPeril|Widget")
	void BP_OpenInteraction(AController* Controller);


	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Widget")
	void CloseInteraction(AController* Controller);

	virtual void CloseInteraction_Implementation(AController* Controller);

	UFUNCTION(BlueprintImplementableEvent, Category = "PurrInPeril|Widget")
	void BP_CloseInteraction(AController* Controller);
	//~ End interaction.

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

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril|Task")
	UPurrInPerilInteractableComponent* InteractableComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril|Task")
	UPurrInPerilSmellProduceComponent* SmellProduceComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PurrInPeril|Widget")
	TSubclassOf<UUserWidget> CustomInteractTipsClass;

	// For extension to multi-player, make a map.
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril|Widget")
	TMap<AController*, UUserWidget*> PlayerToInteractTipsWidgets;

	// Is WidgetComponent a better way to implement widget?
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril|Widget")
	UWidgetComponent* InteractTipsWidgetComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril|Task")
	TMap<AController*, bool> PlayerToPartOfTaskCompleted;
};
