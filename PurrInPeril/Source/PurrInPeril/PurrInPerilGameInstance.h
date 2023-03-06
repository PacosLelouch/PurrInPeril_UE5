// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataAsset.h"
#include "PurrInPerilGameInstance.generated.h"

class UPurrInPerilSaveGame;
class UUserWidget;
class AActor;

UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UIndicateColorMapping : public UDataAsset
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Widget")
	FLinearColor GetColorFromMapping(TSubclassOf<AActor> InClass);

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Widget")
	FLinearColor DefaultColor = FLinearColor::Black;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Widget")
	TMap<TSubclassOf<AActor>, FLinearColor> Mapping;
};

/**
* 
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UPurrInPerilGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UPurrInPerilGameInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Init() override;

	virtual void Shutdown() override;


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril")
	TSubclassOf<UPurrInPerilSaveGame> SaveGameClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril")
	UPurrInPerilSaveGame* SaveGame = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Widget")
	TSubclassOf<UUserWidget> DefaultInteractTipsClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Widget")
	UIndicateColorMapping* IndicateColorMapping;
};
