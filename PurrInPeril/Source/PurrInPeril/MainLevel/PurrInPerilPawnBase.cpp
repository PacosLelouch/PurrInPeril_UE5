// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilPawnBase.h"
#include "Components/BoxComponent.h"
#include "CustomComponents/PurrInPerilMovementComponent.h"

APurrInPerilPawnBase::APurrInPerilPawnBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UPurrInPerilMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
    BoxCollider->SetupAttachment(RootComponent);

	BoxCollider->SetCollisionProfileName(UCollisionProfile::BlockAllDynamic_ProfileName);

	BoxCollider->CanCharacterStepUpOn = ECB_No;
	BoxCollider->SetShouldUpdatePhysicsVolume(true);
	BoxCollider->SetCanEverAffectNavigation(false);
	BoxCollider->bDynamicObstacle = true;

    CustomMovement = GetCharacterMovement<UPurrInPerilMovementComponent>();
}