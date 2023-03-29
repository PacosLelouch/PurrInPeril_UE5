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

	UFUNCTION(BlueprintSetter)
	void SetTargetLocation(FVector NewValue);

	UFUNCTION(BlueprintGetter)
	FVector GetTargetLocation() const { return TargetLocation; }

	UFUNCTION(BlueprintSetter)
	void SetTargetActor(AActor* NewActor);

	UFUNCTION(BlueprintGetter)
	AActor* GetTargetActor() const { return TargetActor; }

	UFUNCTION(BlueprintSetter)
	void SetIndicatorColor(FLinearColor NewValue);

	UFUNCTION(BlueprintGetter)
	FLinearColor GetIndicatorColor() const { return IndicatorColor; }

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "PurrInPeril|Widget")
	bool IsBlocked() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "PurrInPeril|Widget")
	void UpdateIndicatorText();

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* IndicatorPanel;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UImage* IndicatorIcon;

	UPROPERTY(EditAnywhere, Category = "PurrInPeril|Widget", Meta = (ClampMin = 0, ClampMax = 1))
	float LongAxisPercent = 0.85f;
	UPROPERTY(EditAnywhere, Category = "PurrInPeril|Widget", Meta = (ClampMin = 0, ClampMax = 1))
	float MinorAixsPercent = 0.85f;
	UPROPERTY(EditAnywhere, Category = "PurrInPeril|Widget", Meta = (ClampMin = 0, ClampMax = 1))
	float OutsideScreenScale = 0.3f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintSetter = "SetTargetActor", BlueprintGetter = "GetTargetActor", Category = "PurrInPeril|Widget")
	AActor* TargetActor = nullptr;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintSetter = "SetTargetLocation", BlueprintGetter = "GetTargetLocation", Category = "PurrInPeril|Widget")
	FVector TargetLocation = FVector::UpVector * 200.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, BlueprintSetter = "SetIndicatorColor", BlueprintGetter = "GetIndicatorColor", Category = "PurrInPeril|Widget")
	FLinearColor IndicatorColor = FLinearColor::Blue;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril|Widget")
	bool bIsActualLocationOutsideScreen = true;

	//FTransform CameraTransform;

protected:
	//void UpdateCameraTransform();

	FVector2D CalculateIndicatorScreenPos(FVector Destination, bool& bOutIsOutsideScreen);

	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};


/**
*
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UIndicatorPanelWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UIndicatorPanelWidget(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	virtual void NativePreConstruct() override;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PurrInPeril|Widget")
	FLinearColor GetColorAndOpacityFromSingleProducer(UPurrInPerilSmellProduceComponent* Producer);

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UCanvasPanel* CanvasPanel;

	UPROPERTY(BlueprintReadOnly, Category = "PurrInPeril|Widget")
	TSet<UIndicatorWidget*> AccurateIndicators;

	//UPROPERTY(BlueprintReadOnly, Category = "PurrInPeril|Widget")
	//TMap<AActor*, UIndicatorWidget*> StatisticActorsToIndicators;

	//UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Widget")
	//bool bCacheActorToIndicator = true;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Widget")
	TSubclassOf<UIndicatorWidget> IndicatorWidgetClass;
};