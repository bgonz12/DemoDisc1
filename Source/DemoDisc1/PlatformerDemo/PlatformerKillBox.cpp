// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerKillBox.h"
#include "Components/BoxComponent.h"

#include "PlatformerCharacter.h"

// Sets default values
APlatformerKillBox::APlatformerKillBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	KillBoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("KillBoxTrigger"));
	SetRootComponent(KillBoxTrigger);
}

// Called when the game starts or when spawned
void APlatformerKillBox::BeginPlay()
{
	Super::BeginPlay();
	
	KillBoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &APlatformerKillBox::OnBeginOverlap);
}

void APlatformerKillBox::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlatformerCharacter* PlayerCharacter = Cast<APlatformerCharacter>(OtherActor);

	if (PlayerCharacter)
	{
		PlayerCharacter->KillPlayer(DeathAnimationType::FALL);
	}
}

