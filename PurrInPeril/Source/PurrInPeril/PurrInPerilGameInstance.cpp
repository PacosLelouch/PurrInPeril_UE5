// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilGameInstance.h"
#include "PurrInPerilSaveGame.h"
#include "GameFramework/Actor.h"

FLinearColor UIndicateColorMapping::GetColorFromMapping(TSubclassOf<AActor> InClass)
{
	for (TSubclassOf<AActor> TempClass = InClass; TempClass != AActor::StaticClass(); TempClass = TempClass->GetSuperClass())
	{
		FLinearColor* ColorPtr = Mapping.Find(TempClass);
		if (ColorPtr)
		{
			return *ColorPtr;
		}
	}
	return DefaultColor;
}

UPurrInPerilGameInstance::UPurrInPerilGameInstance(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
	SaveGameClass = UPurrInPerilSaveGame::StaticClass();
}


void UPurrInPerilGameInstance::Init()
{
	Super::Init();
	if (GEngine)
	{
		SaveGame = NewObject<UPurrInPerilSaveGame>(this, SaveGameClass, TEXT("PurrInPerilSaveGame"));
	}
}

void UPurrInPerilGameInstance::Shutdown()
{
	Super::Shutdown();
}
