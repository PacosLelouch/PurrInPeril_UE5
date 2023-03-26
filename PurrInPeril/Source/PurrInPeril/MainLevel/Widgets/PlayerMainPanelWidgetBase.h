// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerMainPanelWidgetBase.generated.h"

class UCanvasPanel;
class APurrInPerilMainPlayerController;

/**
*
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UPlayerMainPanelWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	UPlayerMainPanelWidgetBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:

protected:
	void NativePreConstruct() override;

	void NativeConstruct() override;

	void NativeDestruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

};

/**
*
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UMainMenuPanelWidgetBase : public UUserWidget
{
	GENERATED_BODY()
public:
	UMainMenuPanelWidgetBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:

protected:

};