// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "CustomComponents/PurrInPerilInteractableComponent.h"
#include "PurrInPerilTaskActorBase.generated.h"

class UPrimitiveComponent;
class UUserWidget;
class UWidgetComponent;
class APurrInPerilMainPlayerController;

/**
* 
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API APurrInPerilTaskActorBase : public AActor, public IInteractableActorInterface
{
	GENERATED_BODY()
public:
	APurrInPerilTaskActorBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	//~ Begin IInteractableActorInterface.
	virtual UPurrInPerilInteractableComponent* GetInteractableComponent_Implementation() override;
	//~ End IInteractableActorInterface.

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

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril")
	UPurrInPerilInteractableComponent* InteractableComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PurrInPeril")
	TSubclassOf<UUserWidget> CustomInteractTipsClass;

	// For extension to multi-player, make a map.
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril")
	TMap<APurrInPerilMainPlayerController*, UUserWidget*> PlayerToInteractTipsWidgets;

	// Is WidgetComponent a better way to implement widget?
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril")
	UWidgetComponent* InteractTipsWidgetComponent = nullptr;
};
