// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilAsset.h"
#include "GameFramework/Actor.h"
#include "PurrInPerilTaskActorBase.h"

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
