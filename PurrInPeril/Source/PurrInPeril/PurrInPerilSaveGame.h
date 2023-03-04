// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "PurrInPerilSaveGame.generated.h"

/** 
*	@see https://docs.unrealengine.com/latest/INT/Gameplay/SaveGame
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UPurrInPerilSaveGame : public USaveGame
{
	/**
	*	@see UGameplayStatics::CreateSaveGameObject
	*	@see UGameplayStatics::SaveGameToSlot
	*	@see UGameplayStatics::DoesSaveGameExist
	*	@see UGameplayStatics::LoadGameFromSlot
	*	@see UGameplayStatics::DeleteGameInSlot
	*/

	GENERATED_BODY()
public:
	UPurrInPerilSaveGame(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
