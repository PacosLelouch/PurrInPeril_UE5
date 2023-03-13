// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlayerMainPanelWidgetBase.h"
#include "PurrInPerilMainPlayerController.h"
#include "Components/CanvasPanel.h"

UPlayerMainPanelWidgetBase::UPlayerMainPanelWidgetBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UPlayerMainPanelWidgetBase::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UPlayerMainPanelWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPlayerMainPanelWidgetBase::NativeDestruct()
{
	Super::NativeDestruct();
}

void UPlayerMainPanelWidgetBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
}
