// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PurrInPerilMainPlayerController.generated.h"

class UUserWidget;
class APurrInPerilTaskActorBase;
class UPlayerMainPanelWidgetBase;


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

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

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

	// Show accurate indicators (OnAccurateSmellBegin).
	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	void ShowAccurateIndicatorWidget();

	// Hide accurate indicators (OnAccurateSmellEnd).
	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	void HideAccurateIndicatorWidget();

	// Should map to "E" button.
	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	bool DoAccurateSmell();

	UFUNCTION(BlueprintPure, Category = "PurrInPeril")
	bool CheckAccurateSmellValid();

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril")
	bool bIsInteractingWithObject = false;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril|Widget")
	UPlayerMainPanelWidgetBase* PlayerMainPanelWidget = nullptr;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PurrInPeril|Widget")
	TSubclassOf<UPlayerMainPanelWidgetBase> CustomPlayerMainPanelWidgetClass;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril")
	APurrInPerilTaskActorBase* InteractingTaskActor = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril|Widget")
	UUserWidget* IndicatorPanelWidget = nullptr;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PurrInPeril|Widget")
	TSubclassOf<UUserWidget> CustomIndicatorPanelWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril|Widget")
	int32 InteractableWidgetZOrder = 4;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril|Widget")
	int32 IndicatorWidgetZOrder = 3;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril|Widget")
	int32 WidgetLockMovementZOrder = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril|Widget")
	int32 PlayerMainPanelWidgetZOrder = 0;

	bool bLastIgnoreMoveInput = false;
};