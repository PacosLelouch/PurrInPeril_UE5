// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PurrInPerilPawnBase.generated.h"

class UBoxComponent;
class UPurrInPerilMovementComponent;

/**
* 
*/
UCLASS(Abstract, BlueprintType, Blueprintable)
class PURRINPERIL_API APurrInPerilPawnBase : public ACharacter
{
	GENERATED_BODY()
public:
	APurrInPerilPawnBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril")
	UBoxComponent* BoxCollider = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril")
	UPurrInPerilMovementComponent* CustomMovement = nullptr;
};