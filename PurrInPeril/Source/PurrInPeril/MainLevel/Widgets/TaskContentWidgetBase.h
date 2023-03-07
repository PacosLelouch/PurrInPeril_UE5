// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TaskContentWidgetBase.generated.h"

class UCanvasPanel;
class UCloseTaskContentWidget;
class APurrInPerilTaskActorBase;

/**
* 
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UTaskContentWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:

	void SetTaskActor(APurrInPerilTaskActorBase* InTaskActor) { TaskActor = InTaskActor; }

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril|Task")
	APurrInPerilTaskActorBase* TaskOwner = nullptr;

protected:
	//UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	//UCloseTaskContentWidget* CloseTaskContentWidget = nullptr;

	//UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidgetAnim))
	//UWidgetAnimation* OpenWidgetAnimation = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "PurrInPeril|Task")
	APurrInPerilTaskActorBase* TaskActor = nullptr;

protected:
	void NativePreConstruct() override;

	void NativeConstruct() override;

	void NativeDestruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Widget")
	void OnCloseWidgetButtonClicked();
};