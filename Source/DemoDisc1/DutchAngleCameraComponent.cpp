// Fill out your copyright notice in the Description page of Project Settings.


#include "DutchAngleCameraComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "DemoDisc1GameInstance.h"

UDutchAngleCameraComponent::UDutchAngleCameraComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	bIsSpooky = false;

	DutchMaxAngle = 10.0f;
	DutchRotateSpeed = 0.05f;
}

void UDutchAngleCameraComponent::BeginPlay()
{
	UWorld* World = GetWorld();
	if (!World) return;

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(World);
	if (!GameInstance) return;

	UDemoDisc1GameInstance* DD1GameInstance = Cast<UDemoDisc1GameInstance>(GameInstance);
	if (!DD1GameInstance) return;

	if (!DD1GameInstance->GetHasSpookyTransitioned())
	{
		SetNormal();

		DD1GameInstance->OnSpookyTransition.AddDynamic(this, &UDutchAngleCameraComponent::SetSpooky);
	}
	else
	{
		SetSpooky();
	}
}

void UDutchAngleCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsSpooky)
	{
		UWorld* World = GetWorld();
		if (!World) return;

		float PerlinValue = FMath::PerlinNoise1D(UKismetSystemLibrary::GetGameTimeInSeconds(World) * DutchRotateSpeed);

		FRotator DutchRotation(0.0f, 0.0f, PerlinValue * DutchMaxAngle);

		SetRelativeRotation(DutchRotation);
	}
}

void UDutchAngleCameraComponent::SetNormal()
{
	bIsSpooky = false;

	SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
}

void UDutchAngleCameraComponent::SetSpooky()
{
	bIsSpooky = true;

	UE_LOG(LogTemp, Warning, TEXT("REEE"));
}