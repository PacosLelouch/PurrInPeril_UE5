// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilTaskActorBase.h"
#include "Engine/GameEngine.h"
#include "Engine/World.h"
#include "PurrInPerilGameInstance.h"
#include "PurrInPerilMainPlayerController.h"
#include "Blueprint/UserWidget.h"


APurrInPerilTaskActorBase::APurrInPerilTaskActorBase(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
    InteractableComponent = CreateDefaultSubobject<UPurrInPerilInteractableComponent>(TEXT("InteractableComponent"));
    InteractableComponent->SetupAttachment(RootComponent);

    //Register Events
    OnActorBeginOverlap.AddDynamic(this, &APurrInPerilTaskActorBase::OnOverlapBegin);
    OnActorEndOverlap.AddDynamic(this, &APurrInPerilTaskActorBase::OnOverlapEnd);
}

void APurrInPerilTaskActorBase::BeginPlay()
{
    Super::BeginPlay();

    UWorld* World = GetWorld();
    if (World)
    {
        UPurrInPerilGameInstance* GameInstance = World->GetGameInstance<UPurrInPerilGameInstance>();
        if (GameInstance)
        {
            if (!CustomInteractTipsClass)
            {
                CustomInteractTipsClass = GameInstance->DefaultInteractTipsClass;
            }
        }
    }
}

UPurrInPerilInteractableComponent* APurrInPerilTaskActorBase::GetInteractableComponent_Implementation()
{
    return InteractableComponent;
}

void APurrInPerilTaskActorBase::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
    OnOverlapBegin_Implementation(OverlappedActor, OtherActor);
    BP_OnOverlapBegin(OverlappedActor, OtherActor);
}

void APurrInPerilTaskActorBase::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{
    OnOverlapEnd_Implementation(OverlappedActor, OtherActor);
    BP_OnOverlapEnd(OverlappedActor, OtherActor);
}

void APurrInPerilTaskActorBase::OnOverlapBegin_Implementation(AActor* OverlappedActor, AActor* OtherActor)
{
    APawn* Pawn = Cast<APawn>(OtherActor);
    if (Pawn)
    {
        AController* Controller = Pawn->GetController();
        if (Controller)
        {
            APurrInPerilMainPlayerController* PlayerController = Cast<APurrInPerilMainPlayerController>(Controller);
            if (PlayerController)
            {
                PlayerController->ActivateInteractableWidget(this);
            }
        }
    }
}

void APurrInPerilTaskActorBase::OnOverlapEnd_Implementation(AActor* OverlappedActor, AActor* OtherActor)
{
    APawn* Pawn = Cast<APawn>(OtherActor);
    if (Pawn)
    {
        AController* Controller = Pawn->GetController();
        if (Controller)
        {
            APurrInPerilMainPlayerController* PlayerController = Cast<APurrInPerilMainPlayerController>(Controller);
            if (PlayerController)
            {
                PlayerController->DeactivateInteractableWidget(this);
            }
        }
    }
}
