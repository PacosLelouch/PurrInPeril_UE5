// Copyright Epic Games, Inc. All Rights Reserved.

#include "IndicatorWidget.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"

void UIndicatorWidget::UpdateCameraTransform()
{
    APlayerController* PlayController = GetOwningPlayer();
    if (!PlayController)
    {
        return;
    }
    CameraTransform.SetLocation(PlayController->PlayerCameraManager->GetCameraLocation());
    CameraTransform.SetRotation(PlayController->PlayerCameraManager->GetCameraRotation().Quaternion());
}

FVector2D UIndicatorWidget::CalculateIndicatorScreenPos(FVector Destination)
{
    FVector2D ScreenPos = FVector2D::ZeroVector;
    APlayerController* PlayController = GetOwningPlayer();
    if (!PlayController)
    {
        return ScreenPos;
    }
    auto LocalDestination = CameraTransform.InverseTransformPositionNoScale(Destination);

    FVector2D DestinationDir = FVector2D(LocalDestination.Y, LocalDestination.Z);
    DestinationDir.Normalize();
    int32 ViewPortX, ViewPortY;
    PlayController->GetViewportSize(ViewPortX, ViewPortY);

    float k = DestinationDir.Y / DestinationDir.X;

    float DesignSizeX = ViewPortX / UWidgetLayoutLibrary::GetViewportScale(this);
    float DesignSizeY = ViewPortY / UWidgetLayoutLibrary::GetViewportScale(this);

    // x: right. y: down.
    float a = LongAxisPercent * DesignSizeX / 2;
    float b = MinorAixsPercent * DesignSizeY / 2;

    // Solution.
    float x = UKismetMathLibrary::SignOfFloat(DestinationDir.X) * UKismetMathLibrary::Sqrt((a * a * b * b) / (b * b + a * a * k * k));
    float y = k * x;
    ScreenPos.X = x;

    ScreenPos.Y = -1 * y;

    FVector2D ScreenPosition;
    if (UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(PlayController, Destination, ScreenPosition, false))
    {
        // Origin: Upper left.
        auto ScreenPosX = ScreenPosition.X;
        auto ScreenPosY = ScreenPosition.Y;

        if (ScreenPosX < DesignSizeX && ScreenPosY < DesignSizeY && ScreenPosX > 0 && ScreenPosY > 0)
        {
            ScreenPosX -= DesignSizeX / 2;
            ScreenPosY -= DesignSizeY / 2;
            if (((ScreenPosX * ScreenPosX) / (a * a) + (ScreenPosY * ScreenPosY) / (b * b)) < 1)
            {
                ScreenPos.X = ScreenPosX;
                ScreenPos.Y = ScreenPosY;
            }
        }
    }
    return ScreenPos;
}

void UIndicatorWidget::NativePreConstruct()
{
    Super::NativePreConstruct();
    SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UIndicatorWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    //if (!TargetComponent)
    //{
    //    // Set invisible.
    //    SetVisibility(ESlateVisibility::Collapsed);
    //    return;
    //}
    
    UpdateCameraTransform();
    IndicatorIcon->SetColorAndOpacity(IndicatorColor);

    FVector Location = TestLocation; // TEST //TargetComponent->GetComponentTransform().GetLocation();
    FVector2D ScreenPos = CalculateIndicatorScreenPos(Location);

    auto* CanvasSlot = Cast<UCanvasPanelSlot>(Slot);
    if (CanvasSlot) {
        CanvasSlot->SetPosition(ScreenPos);
    }
}