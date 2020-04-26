// Fill out your copyright notice in the Description page of Project Settings.


#include "SpookyEnableActorComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"

#include "DemoDisc1GameInstance.h"

// Sets default values for this component's properties
USpookyEnableActorComponent::USpookyEnableActorComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	EnableBehavior = ESpookyEnableBehavior::ALWAYS_ENABLED;
}

// Called when the game starts
void USpookyEnableActorComponent::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (!World) return;

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(World);
	if (!GameInstance) return;

	UDemoDisc1GameInstance* DD1GameInstance = Cast<UDemoDisc1GameInstance>(GameInstance);
	if (!DD1GameInstance) return;

	if (!DD1GameInstance->GetHasSpookyTransitioned())
	{
		// Game is normal
		switch (EnableBehavior)
		{
		case ESpookyEnableBehavior::ALWAYS_ENABLED:
			World->GetTimerManager().SetTimer(InitializeEnableTimerHandle, this, &USpookyEnableActorComponent::Enable, 0.1f, false);
			break;
		case ESpookyEnableBehavior::ENABLED_ON_NORMAL:
			World->GetTimerManager().SetTimer(InitializeEnableTimerHandle, this, &USpookyEnableActorComponent::Enable, 0.1f, false);
			DD1GameInstance->OnSpookyTransition.AddDynamic(this, &USpookyEnableActorComponent::Disable);
			break;
		case ESpookyEnableBehavior::ENABLED_ON_SPOOKY:
			World->GetTimerManager().SetTimer(InitializeEnableTimerHandle, this, &USpookyEnableActorComponent::Disable, 0.1f, false);
			DD1GameInstance->OnSpookyTransition.AddDynamic(this, &USpookyEnableActorComponent::Enable);
			break;
		}
	}
	else
	{
		// Game is spooky
		switch (EnableBehavior)
		{
		case ESpookyEnableBehavior::ALWAYS_ENABLED:
			World->GetTimerManager().SetTimer(InitializeEnableTimerHandle, this, &USpookyEnableActorComponent::Enable, 0.1f, false);
			break;
		case ESpookyEnableBehavior::ENABLED_ON_NORMAL:
			World->GetTimerManager().SetTimer(InitializeEnableTimerHandle, this, &USpookyEnableActorComponent::Disable, 0.1f, false);
			break;
		case ESpookyEnableBehavior::ENABLED_ON_SPOOKY:
			World->GetTimerManager().SetTimer(InitializeEnableTimerHandle, this, &USpookyEnableActorComponent::Enable, 0.1f, false);
			break;
		}
	}

}

void USpookyEnableActorComponent::Enable()
{
	bIsEnabled = true;

	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->SetActorEnableCollision(true);
		Owner->SetActorHiddenInGame(false);
		Owner->SetActorTickEnabled(true);

		APawn* PawnOwner = Cast<APawn>(Owner);
		if (PawnOwner)
		{
			AController* PawnOwnerController = PawnOwner->GetController();

			if (PawnOwnerController)
			{
				PawnOwnerController->SetActorTickEnabled(true);
			}
		}
	}
}

void USpookyEnableActorComponent::Disable()
{
	bIsEnabled = false;

	AActor* Owner = GetOwner();
	if (Owner)
	{
		Owner->SetActorEnableCollision(false);
		Owner->SetActorHiddenInGame(true);
		Owner->SetActorTickEnabled(false);

		APawn* PawnOwner = Cast<APawn>(Owner);
		if (PawnOwner)
		{
			AController* PawnOwnerController = PawnOwner->GetController();

			if (PawnOwnerController)
			{
				PawnOwnerController->SetActorTickEnabled(false);
			}
		}
	}
}

