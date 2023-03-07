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
                UUserWidget* WidgetForPlayer = nullptr;
                UUserWidget** WidgetForPlayerPtr = PlayerToInteractTipsWidgets.Find(PlayerController);
                if (!WidgetForPlayerPtr)
                {
                    WidgetForPlayer = CreateWidget(PlayerController, CustomInteractTipsClass);
                    PlayerToInteractTipsWidgets.Add(PlayerController, WidgetForPlayer);
                }
                else
                {
                    WidgetForPlayer = *WidgetForPlayerPtr;
                }
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
                UUserWidget* WidgetForPlayer = nullptr;
                UUserWidget** WidgetForPlayerPtr = PlayerToInteractTipsWidgets.Find(PlayerController);
                if (WidgetForPlayerPtr)
                {
                    WidgetForPlayer = *WidgetForPlayerPtr;
                }
                PlayerController->DeactivateInteractableWidget(this);
            }
        }
    }
}

void APurrInPerilTaskActorBase::OpenInteraction(AController* Controller)
{
    OpenInteraction_Implementation(Controller);
    BP_OpenInteraction(Controller);
}

void APurrInPerilTaskActorBase::OpenInteraction_Implementation(AController* Controller)
{
}

void APurrInPerilTaskActorBase::CloseInteraction(AController* Controller)
{
    CloseInteraction_Implementation(Controller);
    BP_CloseInteraction(Controller);
}

void APurrInPerilTaskActorBase::CloseInteraction_Implementation(AController* Controller)
{
}

void APurrInPerilTaskActorBase::CompleteThisPartOfTask(AController* Controller)
{
    CompleteThisPartOfTask_Implementation(Controller);
    BP_CompleteThisPartOfTask(Controller);
}

void APurrInPerilTaskActorBase::CompleteThisPartOfTask_Implementation(AController* Controller)
{
    bool* bIsCompletedPtr = PlayerToPartOfTaskCompleted.Find(Controller);
    if (bIsCompletedPtr)
    {
        *bIsCompletedPtr = true;
    }
    else
    {
        PlayerToPartOfTaskCompleted.Add(Controller, true);
    }
}

void APurrInPerilTaskActorBase::ResetThisPartOfTask(AController* Controller)
{
    ResetThisPartOfTask_Implementation(Controller);
    BP_ResetThisPartOfTask(Controller);
}

void APurrInPerilTaskActorBase::ResetThisPartOfTask_Implementation(AController* Controller)
{
    bool* bIsCompletedPtr = PlayerToPartOfTaskCompleted.Find(Controller);
    if (bIsCompletedPtr)
    {
        *bIsCompletedPtr = false;
    }
    else
    {
        PlayerToPartOfTaskCompleted.Add(Controller, false);
    }
}

bool APurrInPerilTaskActorBase::IsThisPartOfTaskCompleted(AController* Controller) const
{
    const bool* bIsCompletedPtr = PlayerToPartOfTaskCompleted.Find(Controller);
    return bIsCompletedPtr && *bIsCompletedPtr;
}
