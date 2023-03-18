// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PurrInPerilMainPlayerController.generated.h"

class UUserWidget;
class APurrInPerilTaskActorBase;
class UPurrInPerilInteractableComponent;
class UPlayerMainPanelWidgetBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPartOfTaskCompleteDynamicDelegate, APurrInPerilTaskActorBase*, TaskActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPartOfTaskResetDynamicDelegate, APurrInPerilTaskActorBase*, TaskActor);

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

	UFUNCTION(BlueprintPure, Category = "PurrInPeril")
	APurrInPerilAnimalPawn* GetControlledAnimalPawn() const;

	// Show interactable tips in trigger box.
	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	bool ActivateInteractableWidget(UPurrInPerilInteractableComponent* ComponentToOpenInteraction);

	// Hide interactable tips out of trigger box.
	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	bool DeactivateInteractableWidget(UPurrInPerilInteractableComponent* ComponentToCloseInteraction);

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
	UPlayerMainPanelWidgetBase* PlayerMainBackgroundPanelWidget = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril|Widget")
	UPlayerMainPanelWidgetBase* PlayerMainForegroundPanelWidget = nullptr;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PurrInPeril|Widget")
	TSubclassOf<UPlayerMainPanelWidgetBase> CustomPlayerMainBackgroundPanelWidgetClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PurrInPeril|Widget")
	TSubclassOf<UPlayerMainPanelWidgetBase> CustomPlayerMainForegroundPanelWidgetClass;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril")
	UPurrInPerilInteractableComponent* InteractingComponent = nullptr;

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
	int32 PlayerMainBackgroundPanelWidgetZOrder = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril|Widget")
	int32 PlayerMainForegroundPanelWidgetZOrder = 100;

	UPROPERTY(BlueprintAssignable, Category = "PurrInPeril|Task")
	FOnPartOfTaskCompleteDynamicDelegate OnPartOfTaskComplete;

	UPROPERTY(BlueprintAssignable, Category = "PurrInPeril|Task")
	FOnPartOfTaskResetDynamicDelegate OnPartOfTaskReset;

	bool bLastIgnoreMoveInput = false;
};