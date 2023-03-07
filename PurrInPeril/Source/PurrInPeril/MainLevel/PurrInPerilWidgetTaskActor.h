// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "PurrInPerilTaskActorBase.h"
#include "PurrInPerilWidgetTaskActor.generated.h"

class UTaskContentWidgetBase;

/**
* 
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API APurrInPerilWidgetTaskActor : public APurrInPerilTaskActorBase
{
	GENERATED_BODY()
public:
	APurrInPerilWidgetTaskActor(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~ Begin interaction.
	virtual void OpenInteraction_Implementation(AController* Controller) override;

	virtual void CloseInteraction_Implementation(AController* Controller) override;
	//~ End interaction.


	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PurrInPeril")
	TSubclassOf<UTaskContentWidgetBase> TaskWidgetClass = nullptr;

	// For extension to multi-player, make a map.
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril")
	TMap<AController*, UTaskContentWidgetBase*> PlayerToTaskWidgets;
};