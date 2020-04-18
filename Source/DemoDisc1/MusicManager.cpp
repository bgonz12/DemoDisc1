// Fill out your copyright notice in the Description page of Project Settings.


#include "MusicManager.h"
#include "Components/AudioComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "DemoDisc1GameInstance.h"

// Sets default values for this component's properties
AMusicManager::AMusicManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryActorTick.bCanEverTick = true;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	SetRootComponent(AudioComponent);

	SpookyValue = 0.0f;
	TargetSpookyValue = 0.0f;

	MusicTransitionLerpSpeed = 5.0f;
}


// Called when the game starts
void AMusicManager::BeginPlay()
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
		TransitionToNormal();

		DD1GameInstance->OnSpookyTransition.AddDynamic(this, &AMusicManager::TransitionToSpooky);
	}
	else
	{
		TransitionToSpooky();
	}
}

void AMusicManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpookyValue = FMath::Lerp(SpookyValue, TargetSpookyValue, MusicTransitionLerpSpeed * DeltaTime);

	if (AudioComponent)
	{
		AudioComponent->SetFloatParameter("Spooky", SpookyValue);
	}
}

void AMusicManager::TransitionToNormal()
{
	TargetSpookyValue = 0.0f;
}

void AMusicManager::TransitionToSpooky()
{
	TargetSpookyValue = 1.0f;
}

