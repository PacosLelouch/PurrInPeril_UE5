// Copyright Epic Games, Inc. All Rights Reserved.

#include "TaskContentWidgetBase.h"
#include "PurrInPerilTaskActorBase.h"
#include "PurrInPerilMainPlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "CloseTaskContentWidget.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"

void UTaskContentWidgetBase::NativePreConstruct()
{
    Super::NativePreConstruct();
}

void UTaskContentWidgetBase::NativeConstruct()
{
    Super::NativeConstruct();
    //if (OpenWidgetAnimation)
    //{
    //    UUMGSequencePlayer* UMGSequencePlayer = PlayAnimation(OpenWidgetAnimation, 0.0f, 1, EUMGSequencePlayMode::Forward, 1.0f, false);
    //}
    //if (CloseTaskContentWidget && CloseTaskContentWidget->Button_CloseWidget)
    //{
    //    CloseTaskContentWidget->Button_CloseWidget->OnClicked.AddDynamic(this, &UTaskContentWidgetBase::OnCloseWidgetButtonClicked);
    //}
}

void UTaskContentWidgetBase::NativeDestruct()
{
    //if (CloseTaskContentWidget && CloseTaskContentWidget->Button_CloseWidget)
    //{
    //    CloseTaskContentWidget->Button_CloseWidget->OnClicked.RemoveDynamic(this, &UTaskContentWidgetBase::OnCloseWidgetButtonClicked);
    //}
    //if (OpenWidgetAnimation)
    //{
    //    UUMGSequencePlayer* UMGSequencePlayer = PlayAnimation(OpenWidgetAnimation, 0.0f, 1, EUMGSequencePlayMode::Reverse, 1.0f, false);
    //}
    Super::NativeDestruct();
}

void UTaskContentWidgetBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
}

void UTaskContentWidgetBase::OnCloseWidgetButtonClicked()
{
    if (TaskOwner)
    {
        IInteractableActorInterface::Execute_CloseInteraction(TaskOwner, GetOwningPlayer());
    }
}
