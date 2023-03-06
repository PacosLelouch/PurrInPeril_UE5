// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "IndicatorWidget.generated.h"

class UCanvasPanel;
class UImage;

/**
* 
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UIndicatorWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril|Widget")
	TSet<USceneComponent*> TargetComponents;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* IndicatorPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* IndicatorIcon;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0, ClampMax = 1))
	float LongAxisPercent = 0.7f;
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0, ClampMax = 1))
	float MinorAixsPercent = 0.7f;

	UPROPERTY(EditAnywhere, Category = "PurrInPeril|Widget")
	FVector TestLocation = FVector::UpVector * 200.0f;

	UPROPERTY(EditAnywhere, Category = "PurrInPeril|Widget")
	FLinearColor IndicatorColor = FLinearColor::Blue;


	//FVector2D ScreenPos;

	FTransform CameraTransform;

protected:
	void UpdateCameraTransform();

	FVector2D CalculateIndicatorScreenPos(FVector Destination);

	void NativePreConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};