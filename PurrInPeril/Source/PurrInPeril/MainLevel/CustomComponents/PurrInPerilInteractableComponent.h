// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "UObject/Interface.h"
#include "PurrInPerilInteractableComponent.generated.h"

class UPurrInPerilInteractableComponent;

UINTERFACE(MinimalAPI, BlueprintType)
class UInteractableActorInterface : public UInterface
{
	GENERATED_BODY()
};

// const TScriptInterface<IInteractableActorInterface>& to show in blueprint function.
class PURRINPERIL_API IInteractableActorInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PurrInPeril")
	UPurrInPerilInteractableComponent* GetInteractableComponent();

};

/**
* 
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UPurrInPerilInteractableComponent : public UBoxComponent
{
	GENERATED_BODY()
public:
	UPurrInPerilInteractableComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
