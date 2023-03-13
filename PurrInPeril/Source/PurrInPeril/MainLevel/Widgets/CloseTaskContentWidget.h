// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CloseTaskContentWidget.generated.h"

class UCanvasPanel;
class UButton;
class APurrInPerilTaskActorBase;

/**
* 
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UCloseTaskContentWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* Button_CloseWidget = nullptr;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};