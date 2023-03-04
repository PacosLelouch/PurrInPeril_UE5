// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PurrInPerilMovementComponent.generated.h"


/**
* 
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UPurrInPerilMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	UPurrInPerilMovementComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

};
