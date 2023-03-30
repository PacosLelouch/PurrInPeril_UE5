// Copyright Epic Games, Inc. All Rights Reserved.

#include "IndicatorWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/Image.h"
#include "Components/CanvasPanel.h"
#include "PurrInPerilMainPlayerController.h"
#include "PurrInPerilAnimalPawn.h"
#include "CustomComponents/PurrInPerilInteractableComponent.h"
#include "CustomComponents/PurrInPerilSmellDiscoverComponent.h"
#include "CustomComponents/PurrInPerilSmellProduceComponent.h"

void UIndicatorWidget::SetTargetLocation(FVector NewValue)
{
    TargetLocation = NewValue;
    FVector Location = TargetLocation; // TEST //TargetComponent->GetComponentTransform().GetLocation();
    FVector2D ScreenPos = CalculateIndicatorScreenPos(Location, bIsActualLocationOutsideScreen);
    //UE_LOG(LogTemp, Log, TEXT("[%s] Test location to screen pos: <%s> -> <%s>"), *GetName(), *Location.ToString(), *ScreenPos.ToString());

    bool bNearest = false;
    if (APurrInPerilAnimalPawn* PlayerPawn = GetOwningPlayer()->GetPawn<APurrInPerilAnimalPawn>())
    {
        if (PlayerPawn->SmellDiscoverComponent && 
            PlayerPawn->SmellDiscoverComponent->PerceivedNearestSmellProducer &&
            PlayerPawn->SmellDiscoverComponent->PerceivedNearestSmellProducer->GetOwner() == TargetActor)
        {
            bNearest = true;
        }
    }

    if (bNearest)
    {
        IndicatorIcon->SetRenderScale(
            FVector2D(NearestScreenScale, NearestScreenScale));
    }
    else
    {
        IndicatorIcon->SetRenderScale(
            bIsActualLocationOutsideScreen ?
            FVector2D(OutsideScreenScale, OutsideScreenScale) :
            FVector2D(1.0f, 1.0f));
    }

    auto* CanvasSlot = Cast<UCanvasPanelSlot>(Slot);
    if (CanvasSlot)
    {
        int32 ViewPortX, ViewPortY;
        GetOwningPlayer()->GetViewportSize(ViewPortX, ViewPortY);

        float DesignSizeX = ViewPortX / UWidgetLayoutLibrary::GetViewportScale(this);
        float DesignSizeY = ViewPortY / UWidgetLayoutLibrary::GetViewportScale(this);
        if (ScreenPos.X < DesignSizeX && ScreenPos.Y < DesignSizeY && ScreenPos.X > 0 && ScreenPos.Y > 0)
        {
            CanvasSlot->SetPosition(ScreenPos);
        }
    }
}

void UIndicatorWidget::SetTargetActor(AActor* NewActor)
{
    TargetActor = NewActor;
    if (TargetActor)
    {
        SetTargetLocation(TargetActor->GetActorLocation());
    }
}

void UIndicatorWidget::SetIndicatorColor(FLinearColor NewValue)
{
    IndicatorColor = NewValue;
    IndicatorIcon->SetColorAndOpacity(IndicatorColor);
}

bool UIndicatorWidget::IsBlocked_Implementation() const
{
    return false;
}

void UIndicatorWidget::UpdateIndicatorText_Implementation()
{

}

FSlateBrush UIndicatorWidget::GetIndicatorIconBrush_Implementation() const
{
    return FSlateBrush();
}

//void UIndicatorWidget::UpdateCameraTransform()
//{
//    APlayerController* PlayerController = GetOwningPlayer();
//    if (!PlayerController)
//    {
//        return;
//    }
//    CameraTransform.SetLocation(PlayerController->PlayerCameraManager->GetCameraLocation());
//    CameraTransform.SetRotation(PlayerController->PlayerCameraManager->GetCameraRotation().Quaternion());
//}

FVector2D UIndicatorWidget::CalculateIndicatorScreenPos(FVector Destination, bool& bOutIsOutsideScreen)
{
    bOutIsOutsideScreen = true;
    FVector2D ScreenPos = FVector2D::ZeroVector;
    APlayerController* PlayerController = GetOwningPlayer();
    if (!PlayerController)
    {
        return ScreenPos;
    }
    FTransform CameraTransform = FTransform(
        PlayerController->PlayerCameraManager->GetCameraRotation(),
        PlayerController->PlayerCameraManager->GetCameraLocation(),
        FVector::OneVector);
    auto LocalDestination = CameraTransform.InverseTransformPositionNoScale(Destination);

    FVector2D DestinationDir = FVector2D(LocalDestination.Y, LocalDestination.Z);
    DestinationDir.Normalize();
    int32 ViewPortX, ViewPortY;
    PlayerController->GetViewportSize(ViewPortX, ViewPortY);

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
    if (UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(PlayerController, Destination, ScreenPosition, false))
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
                bOutIsOutsideScreen = false;
                ScreenPos.X = ScreenPosX;
                ScreenPos.Y = ScreenPosY;
            }
        }
    }
    ScreenPos.X += DesignSizeX / 2;
    ScreenPos.Y += DesignSizeY / 2;
    return ScreenPos;
}

void UIndicatorWidget::NativePreConstruct()
{
    Super::NativePreConstruct();
    SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UIndicatorWidget::NativeConstruct()
{
    Super::NativeConstruct();
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
    
    //UpdateCameraTransform();
    ////UE_LOG(LogTemp, Log, TEXT("[%s] Camera location: <%s>, rotation: <%s>"), *GetName(), *CameraTransform.GetLocation().ToString(), *CameraTransform.GetRotation().Rotator().ToString());
    //IndicatorIcon->SetColorAndOpacity(IndicatorColor);

    //FVector Location = TargetLocation; // TEST //TargetComponent->GetComponentTransform().GetLocation();
    //FVector2D ScreenPos = CalculateIndicatorScreenPos(Location, bIsActualLocationOutsideScreen);
    ////UE_LOG(LogTemp, Log, TEXT("[%s] Test location to screen pos: <%s> -> <%s>"), *GetName(), *Location.ToString(), *ScreenPos.ToString());

    //auto* CanvasSlot = Cast<UCanvasPanelSlot>(Slot);
    //if (CanvasSlot) 
    //{
    //    int32 ViewPortX, ViewPortY;
    //    GetOwningPlayer()->GetViewportSize(ViewPortX, ViewPortY);

    //    float DesignSizeX = ViewPortX / UWidgetLayoutLibrary::GetViewportScale(this);
    //    float DesignSizeY = ViewPortY / UWidgetLayoutLibrary::GetViewportScale(this);
    //    if (ScreenPos.X < DesignSizeX && ScreenPos.Y < DesignSizeY && ScreenPos.X > 0 && ScreenPos.Y > 0)
    //    {
    //        CanvasSlot->SetPosition(ScreenPos);
    //    }
    //}
}

UIndicatorPanelWidget::UIndicatorPanelWidget(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    IndicatorWidgetClass = UIndicatorWidget::StaticClass();
}

void UIndicatorPanelWidget::NativePreConstruct()
{
    Super::NativePreConstruct();
}

void UIndicatorPanelWidget::NativeConstruct()
{
    Super::NativeConstruct();
}

void UIndicatorPanelWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    QUICK_SCOPE_CYCLE_COUNTER(Stat_IndicatorPanelWidget);
    Super::NativeTick(MyGeometry, InDeltaTime);

    for (UIndicatorWidget* Indicator : AccurateIndicators)
    {
        Indicator->SetVisibility(ESlateVisibility::Hidden);
    }

    if (APurrInPerilMainPlayerController* PlayerController = Cast<APurrInPerilMainPlayerController>(GetOwningPlayer()))
    {
        if (APurrInPerilAnimalPawn* MainPawn = PlayerController->GetPawn<APurrInPerilAnimalPawn>())
        {
            if (MainPawn->SmellDiscoverComponent->bIsActivatingAccurateSmell || MainPawn->SmellDiscoverComponent->SmellDistanceParameter.bInaccurateSmellWithTarget)
            {
                const TMap<UPurrInPerilSmellProduceComponent*, float>& Producers = MainPawn->SmellDiscoverComponent->PerceivedSmellProducers;
                
                TSet<AActor*> ProducerOwners;
                ProducerOwners.Reserve(Producers.Num());
                for (auto& ProducerPair : Producers)
                {
                    ProducerOwners.Add(ProducerPair.Key->GetOwner());
                }

                // Modify accurate indicator num.
                while (ProducerOwners.Num() > AccurateIndicators.Num())
                {
                    // Need to add indicators.
                    UIndicatorWidget* NewIndicatorWidget = CreateWidget<UIndicatorWidget>(PlayerController, IndicatorWidgetClass);
                    CanvasPanel->AddChild(NewIndicatorWidget);
                    AccurateIndicators.Add(NewIndicatorWidget);
                }

                // Update StatisticActorsToIndicators.
                TSet<AActor*> UndistributedOwners = ProducerOwners;
                for (UIndicatorWidget* Indicator : AccurateIndicators)
                {
                    AActor* TargetActor = Indicator->GetTargetActor();
                    if (IsValid(TargetActor))
                    {
                        //auto& IndicatorRef = StatisticActorsToIndicators.FindOrAdd(TargetActor, Indicator);
                        //IndicatorRef = Indicator;

                        // CurrentActor is distributed.
                        UndistributedOwners.Remove(TargetActor);
                    }
                }

                //for (auto It = StatisticActorsToIndicators.CreateIterator(); It; ++It)
                //{
                //    AActor* CurrentActor = It->Key;
                //    if (!IsValid(CurrentActor) || !ProducerOwners.Contains(CurrentActor))
                //    {
                //        // Should not be in StatisticActorsToIndicators.
                //        StatisticActorsToIndicators.Remove(CurrentActor);
                //    }
                //}

                // Update accurate indicators.
                auto UndistributedOwnerIt = UndistributedOwners.CreateIterator();
                for (UIndicatorWidget* IndicatorWidget : AccurateIndicators)
                {
                    AActor* TargetActor = IndicatorWidget->GetTargetActor();
                    if (!ProducerOwners.Contains(TargetActor) || !IsValid(TargetActor))
                    {
                        if (UndistributedOwnerIt)
                        {
                            TargetActor = *UndistributedOwnerIt;
                            ++UndistributedOwnerIt;
                        }
                        else
                        {
                            TargetActor = nullptr;
                        }
                    }

                    // Update per indicator.
                    IndicatorWidget->SetTargetActor(TargetActor);
                    if (IsValid(TargetActor) && ProducerOwners.Contains(TargetActor))
                    {
                        IndicatorWidget->IndicatorIcon->SetBrush(IndicatorWidget->GetIndicatorIconBrush());
                        IndicatorWidget->SetIndicatorColor(GetColorAndOpacityFromSingleProducer(ISmellProducerInterface::Execute_GetSmellProduceComponent(TargetActor)));
                        IndicatorWidget->UpdateIndicatorText();
                        if (!IsValid(PlayerController->InteractingComponent) || PlayerController->InteractingComponent->GetOwner() != TargetActor)
                        {
                            IndicatorWidget->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
                        }
                        else
                        {
                            IndicatorWidget->SetVisibility(ESlateVisibility::Hidden);
                        }
                    }
                    else
                    {
                        IndicatorWidget->SetVisibility(ESlateVisibility::Hidden);
                    }
                }
            }
        }
    }
}

FLinearColor UIndicatorPanelWidget::GetColorAndOpacityFromSingleProducer_Implementation(UPurrInPerilSmellProduceComponent* Producer)
{
    return FLinearColor(0.0f, 0.0f, 0.0f, 0.0f);
}
