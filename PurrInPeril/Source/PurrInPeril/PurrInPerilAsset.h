// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PurrInPerilAsset.generated.h"

class AActor;
class APurrInPerilTaskActorBase;

UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UIndicateColorMapping : public UDataAsset
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "PurrInPeril|Widget")
	FLinearColor GetColorFromMapping(TSubclassOf<AActor> InClass) const;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Widget")
	FLinearColor DefaultColor = FLinearColor::Black;

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Widget")
	TMap<TSubclassOf<AActor>, FLinearColor> Mapping;
};


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

UCLASS(BlueprintType, Blueprintable)
class PURRINPERIL_API UTaskIdentifierMapping : public UDataAsset
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "PurrInPeril")
	FPurrInPerilTaskIdentifier GetIdentifier(TSubclassOf<APurrInPerilTaskActorBase> InClass) const;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Task")
	FPurrInPerilTaskIdentifier DefaultTaskIdentifier;

protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PurrInPeril|Task")
	TMap<TSubclassOf<APurrInPerilTaskActorBase>, FPurrInPerilTaskIdentifier> Mapping;
};