// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "UObject/Interface.h"
#include "PurrInPerilSmellProduceComponent.generated.h"

class UPurrInPerilSmellProduceComponent;

UINTERFACE(MinimalAPI, BlueprintType)
class USmellProducerInterface : public UInterface
{
	GENERATED_BODY()
};

// const TScriptInterface<IInteractableActorInterface>& to show in blueprint function.
class PURRINPERIL_API ISmellProducerInterface
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PurrInPeril")
	UPurrInPerilSmellProduceComponent* GetSmellProduceComponent();

};

/**
* 
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UPurrInPerilSmellProduceComponent : public USceneComponent
{
	GENERATED_BODY()
public:
	UPurrInPerilSmellProduceComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	bool bWithSmell = true;
};
