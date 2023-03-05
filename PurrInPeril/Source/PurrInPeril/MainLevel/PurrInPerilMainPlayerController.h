// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PurrInPerilMainPlayerController.generated.h"

class UUserWidget;
class APurrInPerilTaskActorBase;

/**
* 
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API APurrInPerilMainPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	APurrInPerilMainPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	bool ActivateInteractableWidget(APurrInPerilTaskActorBase* TaskActorToActivate);

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	bool DeactivateInteractableWidget(APurrInPerilTaskActorBase* TaskActorToActivate);

	//UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril")
	//UUserWidget* InteractTipsWidget = nullptr;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril")
	APurrInPerilTaskActorBase* InteractingTaskActor = nullptr;
};