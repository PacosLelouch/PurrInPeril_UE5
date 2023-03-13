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
	//UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril|Widget")
	//TSet<USceneComponent*> TargetComponents;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* IndicatorPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* IndicatorIcon;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0, ClampMax = 1))
	float LongAxisPercent = 0.75f;
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0, ClampMax = 1))
	float MinorAixsPercent = 0.75f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril|Widget")
	FVector TargetLocation = FVector::UpVector * 200.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril|Widget")
	FLinearColor IndicatorColor = FLinearColor::Blue;

	FTransform CameraTransform;

protected:
	void UpdateCameraTransform();

	FVector2D CalculateIndicatorScreenPos(FVector Destination);

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};