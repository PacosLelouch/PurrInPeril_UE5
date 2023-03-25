// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilAsset.h"
#include "GameFramework/Actor.h"
#include "PurrInPerilTaskActorBase.h"
#include "PurrInPerilGameInstance.h"

const UIndicateColorMapping* UIndicateColorMapping::GetFromGameInstance(UObject* WorldContextObject)
{
	if (UWorld* World = WorldContextObject->GetWorld())
	{
		if (UPurrInPerilGameInstance* GameInstance = World->GetGameInstance<UPurrInPerilGameInstance>())
		{
			return GameInstance->IndicateColorMapping;
		}
	}
	return nullptr;
}

FLinearColor UIndicateColorMapping::GetColorFromMapping(TSubclassOf<AActor> InClass) const
{
	for (TSubclassOf<AActor> TempClass = InClass; TempClass != AActor::StaticClass(); TempClass = TempClass->GetSuperClass())
	{
		const FLinearColor* ColorPtr = Mapping.Find(TempClass);
		if (ColorPtr)
		{
			return *ColorPtr;
		}
	}
	return DefaultColor;
}

const UTaskIdentifierMapping* UTaskIdentifierMapping::GetFromGameInstance(UObject* WorldContextObject)
{
	if (UWorld* World = WorldContextObject->GetWorld())
	{
		if (UPurrInPerilGameInstance* GameInstance = World->GetGameInstance<UPurrInPerilGameInstance>())
		{
			return GameInstance->TaskIdentifierMapping;
		}
	}
	return nullptr;
}

FPurrInPerilTaskIdentifier UTaskIdentifierMapping::GetIdentifier(TSubclassOf<APurrInPerilTaskActorBase> InClass) const
{
	for (TSubclassOf<APurrInPerilTaskActorBase> TempClass = InClass; TempClass != APurrInPerilTaskActorBase::StaticClass(); TempClass = TempClass->GetSuperClass())
	{
		const FPurrInPerilTaskIdentifier* TaskIdentifierPtr = Mapping.Find(TempClass);
		if (TaskIdentifierPtr)
		{
			return *TaskIdentifierPtr;
		}
	}
	return DefaultTaskIdentifier;
}

const UTaskParameterOverrideMapping* UTaskParameterOverrideMapping::GetFromGameInstance(UObject* WorldContextObject)
{
	if (UWorld* World = WorldContextObject->GetWorld())
	{
		if (UPurrInPerilGameInstance* GameInstance = World->GetGameInstance<UPurrInPerilGameInstance>())
		{
			return GameInstance->TaskParameterOverrideMapping;
		}
	}
	return nullptr;
}

FInLevelTaskParameter UTaskParameterOverrideMapping::GetTaskParameter(TSubclassOf<APurrInPerilTaskActorBase> InClass) const
{
	for (TSubclassOf<APurrInPerilTaskActorBase> TempClass = InClass; TempClass != APurrInPerilTaskActorBase::StaticClass(); TempClass = TempClass->GetSuperClass())
	{
		const FInLevelTaskParameter* TaskParameterPtr = Mapping.Find(TempClass);
		if (TaskParameterPtr)
		{
			return *TaskParameterPtr;
		}
	}
	return DefaultInLevelTaskParameter;
}

const UGameplayNumericalSettings* UGameplayNumericalSettings::GetFromGameInstance(UObject* WorldContextObject)
{
	if (UWorld* World = WorldContextObject->GetWorld())
	{
		if (UPurrInPerilGameInstance* GameInstance = World->GetGameInstance<UPurrInPerilGameInstance>())
		{
			return GameInstance->GameplayNumericalSettings;
		}
	}
	return nullptr;
}

const UUserWidgetClassSettings* UUserWidgetClassSettings::GetFromGameInstance(UObject* WorldContextObject)
{
	if (UWorld* World = WorldContextObject->GetWorld())
	{
		if (UPurrInPerilGameInstance* GameInstance = World->GetGameInstance<UPurrInPerilGameInstance>())
		{
			return GameInstance->UserWidgetClassSettings;
		}
	}
	return nullptr;
}

const UGameplayAudioSettings* UGameplayAudioSettings::GetFromGameInstance(UObject* WorldContextObject)
{
	if (UWorld* World = WorldContextObject->GetWorld())
	{
		if (UPurrInPerilGameInstance* GameInstance = World->GetGameInstance<UPurrInPerilGameInstance>())
		{
			return GameInstance->AudioSettings;
		}
	}
	return nullptr;
}

bool UPurrInPerilAssetLibrary::EqualEqual_PurrInPerilTaskIdentifierPurrInPerilTaskIdentifier(FPurrInPerilTaskIdentifier A, FPurrInPerilTaskIdentifier B)
{
	return A == B;
}

bool UPurrInPerilAssetLibrary::NotEqual_PurrInPerilTaskIdentifierPurrInPerilTaskIdentifier(FPurrInPerilTaskIdentifier A, FPurrInPerilTaskIdentifier B)
{
	return !(A == B);
}

const UIndicateColorMapping* UPurrInPerilAssetLibrary::GetIndicateColorMappingFromGameInstance(UObject* WorldContextObject)
{
	return UIndicateColorMapping::GetFromGameInstance(WorldContextObject);
}

const UTaskIdentifierMapping* UPurrInPerilAssetLibrary::GetTaskIdentifierMappingFromGameInstance(UObject* WorldContextObject)
{
	return UTaskIdentifierMapping::GetFromGameInstance(WorldContextObject);
}

const UTaskParameterOverrideMapping* UPurrInPerilAssetLibrary::GetTaskParameterOverrideMappingFromGameInstance(UObject* WorldContextObject)
{
	return UTaskParameterOverrideMapping::GetFromGameInstance(WorldContextObject);
}

const UGameplayNumericalSettings* UPurrInPerilAssetLibrary::GetGameplayNumericalSettingsFromGameInstance(UObject* WorldContextObject)
{
	return UGameplayNumericalSettings::GetFromGameInstance(WorldContextObject);
}

const UUserWidgetClassSettings* UPurrInPerilAssetLibrary::GetUserWidgetClassSettingsFromGameInstance(UObject* WorldContextObject)
{
	return UUserWidgetClassSettings::GetFromGameInstance(WorldContextObject);
}

const UGameplayAudioSettings* UPurrInPerilAssetLibrary::GetGameplayAudioSettingsFromGameInstance(UObject* WorldContextObject)
{
	return UGameplayAudioSettings::GetFromGameInstance(WorldContextObject);
}

