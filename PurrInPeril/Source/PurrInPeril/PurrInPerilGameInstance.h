// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PurrInPerilGameInstance.generated.h"

class UPurrInPerilSaveGame;
class UUserWidget;
class AActor;
class UIndicateColorMapping;
class UTaskIdentifierMapping;
class UPlayerMainPanelWidgetBase;
class UGameplayNumericalSettings;
class UUserWidgetClassSettings;
class UGameplayAudioSettings;

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


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Asset")
	const UIndicateColorMapping* IndicateColorMapping;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Asset")
	const UTaskIdentifierMapping* TaskIdentifierMapping;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Asset")
	const UGameplayNumericalSettings* GameplayNumericalSettings;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Asset")
	const UUserWidgetClassSettings* UserWidgetClassSettings;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Asset")
	const UGameplayAudioSettings* AudioSettings;

};
