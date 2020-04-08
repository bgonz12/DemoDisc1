// Fill out your copyright notice in the Description page of Project Settings.


#include "SpookySwapComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

#include "DemoDisc1GameInstance.h"

// Sets default values for this component's properties
USpookySwapComponent::USpookySwapComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	bIsSpooky = false;
}

void USpookySwapComponent::Initialize()
{
	UWorld* World = GetWorld();
	if (!World) return;

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(World);
	if (!GameInstance) return;

	UDemoDisc1GameInstance* DD1GameInstance = Cast<UDemoDisc1GameInstance>(GameInstance);
	if (!DD1GameInstance) return;

	if (!DD1GameInstance->GetHasSpookyTransitioned())
	{
		DisplayNormal();

		DD1GameInstance->OnSpookyTransition.AddDynamic(this, &USpookySwapComponent::DisplaySpooky);
	}
	else
	{
		DisplaySpooky();
	}
}

void USpookySwapComponent::AddNormalComponent(UPrimitiveComponent* Component)
{
	if (!Component)
	{
		UE_LOG(LogTemp, Error, TEXT("Attempting to add NULL NormalComponent to SpookySwapComponent"));
		return;
	}

	if (NormalComponents.Num() <= 0)
	{
		EnabledNormalCollision = Component->GetCollisionEnabled();
	}

	NormalComponents.Add(Component);
}

void USpookySwapComponent::AddSpookyComponent(UPrimitiveComponent* Component)
{
	if (!Component)
	{
		UE_LOG(LogTemp, Error, TEXT("Attempting to add NULL SpookyComponent to SpookySwapComponent"));
		return;
	}

	if (SpookyComponents.Num() <= 0)
	{
		EnabledSpookyCollision = Component->GetCollisionEnabled();
	}

	SpookyComponents.Add(Component);
}

void USpookySwapComponent::DisplayNormal()
{
	bIsSpooky = false;

	// Disable spooky components
	for (UPrimitiveComponent* Component : SpookyComponents)
	{
		Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Component->SetVisibility(false);
	}

	// Enable normal components
	for (UPrimitiveComponent* Component : NormalComponents)
	{
		Component->SetCollisionEnabled(EnabledNormalCollision);
		Component->SetVisibility(true);
	}
}

void USpookySwapComponent::DisplaySpooky()
{
	bIsSpooky = true;

	// Disable normal components
	for (UPrimitiveComponent* Component : NormalComponents)
	{
		Component->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		Component->SetVisibility(false);
	}

	// Enable spooky components
	for (UPrimitiveComponent* Component : SpookyComponents)
	{
		Component->SetCollisionEnabled(EnabledSpookyCollision);
		Component->SetVisibility(true);
	}
}

