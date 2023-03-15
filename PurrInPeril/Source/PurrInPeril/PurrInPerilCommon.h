// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "PurrInPerilCommon.generated.h"


USTRUCT(BlueprintType)
struct PURRINPERIL_API FPurrInPerilTaskIdentifier
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril|Task")
	int32 ID = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril|Task")
	FName TaskName = TEXT("Default");

	bool operator==(const FPurrInPerilTaskIdentifier& Other) const
	{
		return ID == Other.ID &&
			TaskName == Other.TaskName;
	}
};

template<> struct TIsPODType<FPurrInPerilTaskIdentifier> { enum { Value = true }; };

FORCEINLINE uint32 GetTypeHash(const FPurrInPerilTaskIdentifier& Struct)
{
	uint32 Hash = FCrc::MemCrc32(&Struct, sizeof(Struct));
	return Hash;
}

USTRUCT(BlueprintType)
struct PURRINPERIL_API FPlayerStateParameter
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	float SanityValue = 100.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	float HungerValue = 100.0f;
};

USTRUCT(BlueprintType)
struct PURRINPERIL_API FSmellDistanceParameter
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	float MaxSmellDistance = 5000.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	float MinSmellDistance = 200.0f;
};

USTRUCT(BlueprintType)
struct PURRINPERIL_API FInLevelCostParameter
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	float AccurateSmellCost = 20.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	float HungerValueLostPerSecond = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	int32 CatFoodDurability = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	float CatFoodRecoveryHungerValue = 20.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	int32 CatMintDurability = -1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	float CatMintRecoverySanityValue = 20.0f;
};

USTRUCT(BlueprintType)
struct PURRINPERIL_API FInLevelEnemyParameter
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	float SanityValueDamagePerEnemyPerSecond = 1.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	float MaxDamagingDistance = 3000.0f;
};

USTRUCT(BlueprintType)
struct PURRINPERIL_API FInLevelTimeParameter
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	float InitialGameCountdownInSecond = 180.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "PurrInPeril")
	float AccurateSmellDurationInSecond = 10.0f;
};