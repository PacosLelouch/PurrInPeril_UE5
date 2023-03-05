// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "IndicatorWidget.generated.h"


/**
* 
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UIndicatorWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril")
	USceneComponent* TargetComponent = nullptr;

protected:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* IndicatorIcon;

	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0, ClampMax = 1))
	float LongAxisPercent = 0.7f;
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0, ClampMax = 1))
	float MinorAixsPercent = 0.7f;

	FVector2D ScreenPos;

	FTransform CameraTransform;

protected:
	void CalculateIndicatorScreenPos(FVector Destination);

	void NativePreConstruct() override;

	void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};