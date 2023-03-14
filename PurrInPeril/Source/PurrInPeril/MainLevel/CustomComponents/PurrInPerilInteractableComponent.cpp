// Copyright Epic Games, Inc. All Rights Reserved.

#include "PurrInPerilInteractableComponent.h"
#include "GameFramework/Actor.h"
#include "PurrInPerilMainPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "PurrInPerilAsset.h"

namespace
{
    static const FColor TriggerBaseColor(100, 255, 100, 255);
    static const FName TriggerCollisionProfileName(TEXT("Trigger"));
}

UPurrInPerilInteractableComponent::UPurrInPerilInteractableComponent(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    ShapeColor = TriggerBaseColor;
    SetGenerateOverlapEvents(true);
    SetCollisionProfileName(TriggerCollisionProfileName);

    //OnComponentBeginOverlap.AddDynamic(this, &UPurrInPerilInteractableComponent::OnOverlapBegin);
    //OnComponentEndOverlap.AddDynamic(this, &UPurrInPerilInteractableComponent::OnOverlapEnd);
}

void UPurrInPerilInteractableComponent::BeginPlay()
{
    Super::BeginPlay();

    if (const UUserWidgetClassSettings* UserWidgetClassSettings = UUserWidgetClassSettings::GetFromGameInstance(this))
    {
        if (!CustomInteractTipsClass)
        {
            CustomInteractTipsClass = UserWidgetClassSettings->DefaultInteractTipsClass;
        }
    }

    AActor* OwnerActor = GetOwner();
    if (OwnerActor)
    {
        OwnerActor->OnActorBeginOverlap.AddDynamic(this, &UPurrInPerilInteractableComponent::OnActorOverlapBegin);
        OwnerActor->OnActorEndOverlap.AddDynamic(this, &UPurrInPerilInteractableComponent::OnActorOverlapEnd);
    }
}

void UPurrInPerilInteractableComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    AActor* OwnerActor = GetOwner();
    if (OwnerActor)
    {
        OwnerActor->OnActorBeginOverlap.RemoveDynamic(this, &UPurrInPerilInteractableComponent::OnActorOverlapBegin);
        OwnerActor->OnActorEndOverlap.RemoveDynamic(this, &UPurrInPerilInteractableComponent::OnActorOverlapEnd);
    }
    Super::EndPlay(EndPlayReason);
}

void UPurrInPerilInteractableComponent::OnActorOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
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

void UPurrInPerilInteractableComponent::OnActorOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
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

//void UPurrInPerilInteractableComponent::OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//}
//
//void UPurrInPerilInteractableComponent::OnComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//}
