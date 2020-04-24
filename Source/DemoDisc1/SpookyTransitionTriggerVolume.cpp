// Fill out your copyright notice in the Description page of Project Settings.


#include "SpookyTransitionTriggerVolume.h"
#include "Kismet/GameplayStatics.h"

#include "DemoDisc1GameInstance.h"

// Sets default values
ASpookyTransitionTriggerVolume::ASpookyTransitionTriggerVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASpookyTransitionTriggerVolume::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ASpookyTransitionTriggerVolume::BeginOverlap);
}

// Called every frame
void ASpookyTransitionTriggerVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpookyTransitionTriggerVolume::BeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	UWorld* World = GetWorld();
	if (!World) return;

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(World);
	if (!GameInstance) return;

	UDemoDisc1GameInstance* DD1GameInstance = Cast<UDemoDisc1GameInstance>(GameInstance);
	if (!DD1GameInstance) return;

	if (DD1GameInstance->GetIsTransitionTime())
	{
		DD1GameInstance->TriggerSpookyTransition();

		if (TransitionSound)
		{
			UGameplayStatics::PlaySound2D(World, TransitionSound);
		}
	}
}

