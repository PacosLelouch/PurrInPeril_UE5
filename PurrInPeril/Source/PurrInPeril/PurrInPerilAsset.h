// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PurrInPerilCommon.h"
#include "PurrInPerilAsset.generated.h"

class AActor;
class APurrInPerilTaskActorBase;
class UUserWidget;
class UPlayerMainPanelWidgetBase;

UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UIndicateColorMapping : public UDataAsset
{
	GENERATED_BODY()
public:
	static const UIndicateColorMapping* GetFromGameInstance(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Widget")
	FLinearColor GetColorFromMapping(TSubclassOf<AActor> InClass) const;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Widget")
	FLinearColor DefaultColor = FLinearColor::Black;

protected:

	UPROPERTY(EditAnywhere, Category = "PurrInPeril|Widget")
	TMap<TSubclassOf<AActor>, FLinearColor> Mapping;
};

UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UTaskIdentifierMapping : public UDataAsset
{
	GENERATED_BODY()
public:
	static const UTaskIdentifierMapping* GetFromGameInstance(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Task")
	FPurrInPerilTaskIdentifier GetIdentifier(TSubclassOf<APurrInPerilTaskActorBase> InClass) const;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Task")
	FPurrInPerilTaskIdentifier DefaultTaskIdentifier;

protected:

	UPROPERTY(EditAnywhere, Category = "PurrInPeril|Task")
	TMap<TSubclassOf<APurrInPerilTaskActorBase>, FPurrInPerilTaskIdentifier> Mapping;
};

UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UTaskParameterOverrideMapping : public UDataAsset
{
	GENERATED_BODY()
public:
	static const UTaskParameterOverrideMapping* GetFromGameInstance(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Task")
	FInLevelTaskParameter GetTaskParameter(TSubclassOf<APurrInPerilTaskActorBase> InClass) const;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Task")
	FInLevelTaskParameter DefaultInLevelTaskParameter;

protected:
	UPROPERTY(EditAnywhere, Category = "PurrInPeril|Task")
	TMap<TSubclassOf<APurrInPerilTaskActorBase>, FInLevelTaskParameter> Mapping;
};

UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UGameplayNumericalSettings : public UDataAsset
{
	GENERATED_BODY()
public:
	static const UGameplayNumericalSettings* GetFromGameInstance(UObject* WorldContextObject);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril")
	FPlayerStateParameter DefaultPlayerStateParameter;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril")
	FSmellDistanceParameter DefaultSmellDistanceParameter;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril")
	FInLevelCostParameter DefaultInLevelCostParameter;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril")
	FInLevelTimeParameter DefaultInLevelTimeParameter;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril")
	FInLevelEnemyParameter DefaultInLevelEnemyParameter;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Task")
	FInLevelTaskParameter DefaultInLevelTaskParameter;
};

UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UUserWidgetClassSettings : public UDataAsset
{
	GENERATED_BODY()
public:
	static const UUserWidgetClassSettings* GetFromGameInstance(UObject* WorldContextObject);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Widget")
	TSubclassOf<UPlayerMainPanelWidgetBase> DefaultPlayerMainBackgroundPanelWidgetClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Widget")
	TSubclassOf<UPlayerMainPanelWidgetBase> DefaultPlayerMainForegroundPanelWidgetClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Widget")
	TSubclassOf<UUserWidget> DefaultInteractTipsClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Widget")
	TSubclassOf<UUserWidget> DefaultIndicatorPanelWidgetClass;
};

UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UGameplayAudioSettings : public UDataAsset
{
	GENERATED_BODY()
public:
	static const UGameplayAudioSettings* GetFromGameInstance(UObject* WorldContextObject);

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Audio")
	FInLevelAudioSettings InLevelAudioSettings;
};

//UCLASS(BlueprintType, Blueprintable)
//class PURRINPERIL_API UBlueprintStructureAsset : public UDataAsset
//{
//	GENERATED_BODY()
//public:
//	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril")
//	class UUserDefinedStruct* Struct = nullptr;
//};


UCLASS(BlueprintType)
class PURRINPERIL_API UPurrInPerilAssetLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (DisplayName = "Equal (PurrInPerilTaskIdentifier)", CompactNodeTitle = "==", Keywords = "== equal"), Category = "PurrInPeril")
	static bool EqualEqual_PurrInPerilTaskIdentifierPurrInPerilTaskIdentifier(FPurrInPerilTaskIdentifier A, FPurrInPerilTaskIdentifier B);
	
	UFUNCTION(BlueprintPure, meta = (DisplayName = "NotEqual (PurrInPerilTaskIdentifier)", CompactNodeTitle = "!=", Keywords = "!= not equal"), Category = "PurrInPeril")
	static bool NotEqual_PurrInPerilTaskIdentifierPurrInPerilTaskIdentifier(FPurrInPerilTaskIdentifier A, FPurrInPerilTaskIdentifier B);

	UFUNCTION(BlueprintPure, Category = "PurrInPeril", meta = (WorldContext = "WorldContextObject"))
	static const UIndicateColorMapping* GetIndicateColorMappingFromGameInstance(UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "PurrInPeril", meta = (WorldContext = "WorldContextObject"))
	static const UTaskIdentifierMapping* GetTaskIdentifierMappingFromGameInstance(UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "PurrInPeril", meta = (WorldContext = "WorldContextObject"))
	static const UTaskParameterOverrideMapping* GetTaskParameterOverrideMappingFromGameInstance(UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "PurrInPeril", meta = (WorldContext = "WorldContextObject"))
	static const UGameplayNumericalSettings* GetGameplayNumericalSettingsFromGameInstance(UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "PurrInPeril", meta = (WorldContext = "WorldContextObject"))
	static const UUserWidgetClassSettings* GetUserWidgetClassSettingsFromGameInstance(UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "PurrInPeril|Audio", meta = (WorldContext = "WorldContextObject"))
	static const UGameplayAudioSettings* GetGameplayAudioSettingsFromGameInstance(UObject* WorldContextObject);
};