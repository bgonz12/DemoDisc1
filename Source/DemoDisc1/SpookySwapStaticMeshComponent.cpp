// Fill out your copyright notice in the Description page of Project Settings.


#include "SpookySwapStaticMeshComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "DemoDisc1GameInstance.h"

void USpookySwapStaticMeshComponent::BeginPlay()
{
	EnabledCollision = GetCollisionEnabled();

	UWorld* World = GetWorld();
	if (!World) return;

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(World);
	if (!GameInstance) return;

	UDemoDisc1GameInstance* DD1GameInstance = Cast<UDemoDisc1GameInstance>(GameInstance);
	if (!DD1GameInstance) return;

	if (!DD1GameInstance->GetHasSpookyTransitioned())
	{
		SwapToNormal();

		DD1GameInstance->OnSpookyTransition.AddDynamic(this, &USpookySwapStaticMeshComponent::SwapToSpooky);
	}
	else
	{
		SwapToSpooky();
	}
}

void USpookySwapStaticMeshComponent::SwapToNormal()
{
	if (!bIsSpooky)
	{
		// Enable normal mesh
		SetCollisionEnabled(EnabledCollision);
		SetVisibility(true);
	}
	else
	{
		// Disable spooky mesh
		SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SetVisibility(false);
	}
}

void USpookySwapStaticMeshComponent::SwapToSpooky()
{
	if(bIsSpooky)
	{
		// Enable spooky mesh
		SetCollisionEnabled(EnabledCollision);
		SetVisibility(true);
	}
	else
	{
		// Disable normal mesh
		SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SetVisibility(false);
	}
}