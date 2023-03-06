// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PurrInPerilMainPlayerController.generated.h"

class UUserWidget;
class APurrInPerilTaskActorBase;

/**
* 
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API APurrInPerilMainPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	APurrInPerilMainPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	// Show interactable tips in trigger box.
	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	bool ActivateInteractableWidget(APurrInPerilTaskActorBase* TaskActorToActivate);

	// Hide interactable tips out of trigger box.
	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	bool DeactivateInteractableWidget(APurrInPerilTaskActorBase* TaskActorToActivate);

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	void OpenWidgetLockMovement(UUserWidget* UserWidget);

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	void CloseWidgetUnlockMovement(UUserWidget* UserWidget);

	// Should map to "E" button.
	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	bool DoAccurateSmell();

	UFUNCTION(BlueprintPure, Category = "PurrInPeril")
	bool CheckAccurateSmellValid();

	//UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril")
	//UUserWidget* InteractTipsWidget = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril")
	APurrInPerilTaskActorBase* InteractingTaskActor = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	int32 InteractableWidgetZOrder = 4;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	int32 WidgetLockMovementZOrder = 0;

	bool bLastIgnoreMoveInput = false;
};