// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PurrInPerilMainPlayerController.generated.h"

class UUserWidget;
class APurrInPerilTaskActorBase;
class UPurrInPerilInteractableComponent;
class UPlayerMainPanelWidgetBase;
class UMainMenuPanelWidgetBase;

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
	bool DeactivateInteractableWidget(UPurrInPerilInteractableComponent* ComponentToCloseInteraction, bool bClearInteractingComponent = true);

	// Callback PostActivateInteractableWidget.
	UFUNCTION(BlueprintNativeEvent, Category = "PurrInPeril")
	void PostActivateInteractableWidget(UPurrInPerilInteractableComponent* ComponentToOpenInteraction);

	// Callback PostDeactivateInteractableWidget.
	UFUNCTION(BlueprintNativeEvent, Category = "PurrInPeril")
	void PostDeactivateInteractableWidget(UPurrInPerilInteractableComponent* ComponentToOpenInteraction, bool bClearInteractingComponent);


	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	void OpenWidgetLockMovement(UUserWidget* UserWidget);

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	void CloseWidgetUnlockMovement(UUserWidget* UserWidget);


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PurrInPeril")
	void OpenMainMenu();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PurrInPeril")
	void CloseMainMenu();


	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	void PushIgnoreGameInput(bool bIsGameInputIgnored);

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	void PopIgnoreGameInput();


	// Callback OnAccurateSmellBegin.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PurrInPeril")
	void OnAccurateSmellBegin();

	// Callback OnAccurateSmellEnd.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PurrInPeril")
	void OnAccurateSmellEnd();

	// Should map to "Q" button.
	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Smell")
	bool DoAccurateSmell();

	UFUNCTION(BlueprintPure, Category = "PurrInPeril|Smell")
	bool CheckAccurateSmellValid();

	UFUNCTION(Exec, BlueprintCallable, Category = "PurrInPeril")
	bool AddSanityValue(float AddValue);

	UFUNCTION(Exec, BlueprintCallable, Category = "PurrInPeril")
	bool AddHungerValue(float AddValue);


	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril")
	bool bIsInteractingWithObject = false;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril|Widget")
	UPlayerMainPanelWidgetBase* PlayerMainBackgroundPanelWidget = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril|Widget")
	UPlayerMainPanelWidgetBase* PlayerMainForegroundPanelWidget = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril|Widget")
	UMainMenuPanelWidgetBase* MainMenuPanelWidget = nullptr;


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PurrInPeril|Widget")
	TSubclassOf<UPlayerMainPanelWidgetBase> CustomPlayerMainBackgroundPanelWidgetClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PurrInPeril|Widget")
	TSubclassOf<UPlayerMainPanelWidgetBase> CustomPlayerMainForegroundPanelWidgetClass;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PurrInPeril|Widget")
	TSubclassOf<UMainMenuPanelWidgetBase> CustomMainMenuPanelWidgetClass;


	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril")
	UPurrInPerilInteractableComponent* InteractingComponent = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril|Widget")
	UUserWidget* IndicatorPanelWidget = nullptr;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PurrInPeril|Widget")
	TSubclassOf<UUserWidget> CustomIndicatorPanelWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril|Widget")
	int32 InteractableWidgetZOrder = 12;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril|Widget")
	int32 IndicatorWidgetZOrder = 2;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril|Widget")
	int32 WidgetLockMovementZOrder = 11;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril|Widget")
	int32 PlayerMainBackgroundPanelWidgetZOrder = 10;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril|Widget")
	int32 MainMenuPanelWidgetZOrder = 100;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril|Widget")
	int32 PlayerMainForegroundPanelWidgetZOrder = 99;

	UPROPERTY(BlueprintAssignable, Category = "PurrInPeril|Task")
	FOnPartOfTaskCompleteDynamicDelegate OnPartOfTaskComplete;

	UPROPERTY(BlueprintAssignable, Category = "PurrInPeril|Task")
	FOnPartOfTaskResetDynamicDelegate OnPartOfTaskReset;

protected:
	TArray<bool> IgnoreMoveInputStack;
	//bool bLastIgnoreMoveInput = false;
};