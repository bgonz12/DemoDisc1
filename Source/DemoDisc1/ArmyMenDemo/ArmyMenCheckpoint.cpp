// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenCheckpoint.h"
#include "DemoDisc1/ReloadableActor.h"
#include "ArmyMenPlayerCharacter.h"

AArmyMenCheckpoint::AArmyMenCheckpoint()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AArmyMenCheckpoint::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &AArmyMenCheckpoint::BeginOverlap);
}

void AArmyMenCheckpoint::BeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	AArmyMenPlayerCharacter* PlayerCharacter = Cast<AArmyMenPlayerCharacter>(OtherActor);

	if (PlayerCharacter)
	{
		PlayerCharacter->SetRespawnTransform(GetActorTransform());
	}

	for (AActor* Actor : ReloadableActorsToDisable)
	{
		IReloadableActor* ReloadableActor = Cast<IReloadableActor>(Actor);

		if (ReloadableActor)
		{
			ReloadableActor->SetIsReloadable(false);
		}
	}
}