// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PurrInPerilPawnBase.h"
#include "PurrInPerilAsset.h"
#include "CustomComponents/PurrInPerilSmellProduceComponent.h"
#include "PurrInPerilEnemyPawn.generated.h"

class UBoxComponent;
class UPurrInPerilMovementComponent;
class UPurrInPerilHearingComponent;
class UPurrInPerilEnvironmentAudioComponent;

/**
* 
*/
UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API APurrInPerilEnemyPawn : public APurrInPerilPawnBase, public ISmellProducerInterface
{
	GENERATED_BODY()
public:
	APurrInPerilEnemyPawn(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;

	//~ Begin ISmellProducerInterface override.
	virtual UPurrInPerilSmellProduceComponent* GetSmellProduceComponent_Implementation() override;
	//~ End ISmellProducerInterface override.

	UFUNCTION(BlueprintGetter, Category = "PurrInPeril")
	bool IsOverrideInLevelEnemyParameter() const { return bOverrideInLevelEnemyParameter; }

	UFUNCTION(BlueprintGetter, Category = "PurrInPeril")
	const FInLevelEnemyParameter& GetInLevelEnemyParameter() const { return InLevelEnemyParameter; }

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril|Smell")
	UPurrInPerilSmellProduceComponent* SmellProduceComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril|Audio")
	UPurrInPerilHearingComponent* HearingComponent = nullptr;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "PurrInPeril|Audio")
	UPurrInPerilEnvironmentAudioComponent* VoiceComponent = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, BlueprintGetter = "IsOverrideInLevelEnemyParameter", Category = "PurrInPeril")
	bool bOverrideInLevelEnemyParameter = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, BlueprintGetter = "GetInLevelEnemyParameter", Category = "PurrInPeril")
	FInLevelEnemyParameter InLevelEnemyParameter;
};