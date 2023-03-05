// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "PurrInPerilTaskActorBase.h"
#include "PurrInPerilWidgetTaskActor.generated.h"


/**
* 
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API APurrInPerilWidgetTaskActor : public APurrInPerilTaskActorBase
{
	GENERATED_BODY()
public:
	APurrInPerilWidgetTaskActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PurrInPeril")
	TSubclassOf<UUserWidget> TaskWidgetClass = nullptr;
};