// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilGameInstance.h"
#include "PurrInPerilSaveGame.h"
#include "PurrInPerilAsset.h"
#include "GameFramework/Actor.h"

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
