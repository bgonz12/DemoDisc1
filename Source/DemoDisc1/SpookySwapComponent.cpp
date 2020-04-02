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
}

// Called when the game starts
void USpookySwapComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void USpookySwapComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USpookySwapComponent::Initialize()
{
	if (NormalComponents.Num() > 0)
	{
		EnabledNormalCollision = NormalComponents[0]->GetCollisionEnabled();
	}

	if (SpookyComponents.Num() > 0)
	{
		EnabledSpookyCollision = SpookyComponents[0]->GetCollisionEnabled();
	}

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

void USpookySwapComponent::DisplayNormal()
{
	if (NormalComponents.Num() <= 0) return;

	// Set collisions
	for (UPrimitiveComponent* SpookyComponent : SpookyComponents)
	{
		SpookyComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	for (UPrimitiveComponent* NormalComponent : NormalComponents)
	{
		NormalComponent->SetCollisionEnabled(EnabledNormalCollision);
	}

	// Set visibility
	for (UPrimitiveComponent* SpookyComponent : SpookyComponents)
	{
		SpookyComponent->SetVisibility(false);
	}

	for (UPrimitiveComponent* NormalComponent : NormalComponents)
	{
		NormalComponent->SetVisibility(true);
	}
}

void USpookySwapComponent::DisplaySpooky()
{
	if (SpookyComponents.Num() <= 0) return;

	// Set collisions
	for (UPrimitiveComponent* NormalComponent : NormalComponents)
	{
		NormalComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	for (UPrimitiveComponent* SpookyComponent : SpookyComponents)
	{
		SpookyComponent->SetCollisionEnabled(EnabledSpookyCollision);
	}

	// Set visibility
	for (UPrimitiveComponent* NormalComponent : NormalComponents)
	{
		NormalComponent->SetVisibility(false);
	}

	for (UPrimitiveComponent* SpookyComponent : SpookyComponents)
	{
		SpookyComponent->SetVisibility(true);
	}
}
