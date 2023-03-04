// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilPawnBase.h"
#include "Components/BoxComponent.h"
#include "CustomComponents/PurrInPerilMovementComponent.h"

APurrInPerilPawnBase::APurrInPerilPawnBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UPurrInPerilMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
    BoxCollider->SetupAttachment(RootComponent);

    CustomMovement = GetCharacterMovement<UPurrInPerilMovementComponent>();
}