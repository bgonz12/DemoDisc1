// Fill out your copyright notice in the Description page of Project Settings.


#include "SpookySwapActor.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "DemoDisc1GameInstance.h"

// Sets default values
ASpookySwapActor::ASpookySwapActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	bIsSpooky = false;
}

// Called when the game starts or when spawned
void ASpookySwapActor::BeginPlay()
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
		EnableNormal();

		DD1GameInstance->OnSpookyTransition.AddDynamic(this, &ASpookySwapActor::EnableSpooky);
	}
	else
	{
		EnableSpooky();
	}
}

void ASpookySwapActor::EnableNormal()
{
	// Disable spooky actors
	for (AActor* Actor : SpookyActors)
	{
		Actor->SetActorEnableCollision(false);
		Actor->SetActorHiddenInGame(true);
		Actor->SetActorTickEnabled(false);
	}

	// Enable normal actors
	for (AActor* Actor : NormalActors)
	{
		Actor->SetActorEnableCollision(true);
		Actor->SetActorHiddenInGame(false);
		Actor->SetActorTickEnabled(true);
	}
}

void ASpookySwapActor::EnableSpooky()
{
	bIsSpooky = true;

	// Disable normal actors
	for (AActor* Actor : NormalActors)
	{
		Actor->SetActorEnableCollision(false);
		Actor->SetActorHiddenInGame(true);
		Actor->SetActorTickEnabled(false);
	}

	// Enable spooky actors
	for (AActor* Actor : SpookyActors)
	{
		Actor->SetActorEnableCollision(true);
		Actor->SetActorHiddenInGame(false);
		Actor->SetActorTickEnabled(true);
	}
}

