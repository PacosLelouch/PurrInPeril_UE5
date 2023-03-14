// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "UObject/Interface.h"
#include "PurrInPerilInteractableComponent.generated.h"

class UPurrInPerilInteractableComponent;
class AController;
class AActor;
class UUserWidget;
class UWidgetComponent;

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

	// Enter interaction.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PurrInPeril|Widget")
	void OpenInteraction(AController* Controller);

	// Exit interaction.
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "PurrInPeril|Widget")
	void CloseInteraction(AController* Controller);
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

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// declare overlap begin function.
	UFUNCTION()
	void OnActorOverlapBegin(AActor* OverlappedActor, AActor* OtherActor);

	// declare overlap end function.
	UFUNCTION()
	void OnActorOverlapEnd(AActor* OverlappedActor, AActor* OtherActor);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "PurrInPeril|Widget")
	TSubclassOf<UUserWidget> CustomInteractTipsClass;

	// For extension to multi-player, make a map.
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "PurrInPeril|Widget")
	TMap<AController*, UUserWidget*> PlayerToInteractTipsWidgets;

	// Is WidgetComponent a better way to implement widget?
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril|Widget")
	UWidgetComponent* InteractTipsWidgetComponent = nullptr;

	//UFUNCTION()
	//void OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//UFUNCTION()
	//void OnComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
