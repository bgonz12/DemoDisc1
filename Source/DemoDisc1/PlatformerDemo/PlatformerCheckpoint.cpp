// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerCheckpoint.h"
#include "Components/BillboardComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

#include "PlatformerCharacter.h"
#include "PlatformerGameModeBase.h"

// Sets default values
APlatformerCheckpoint::APlatformerCheckpoint()
{
	PrimaryActorTick.bCanEverTick = false;

	PlayerSpawnPoint = CreateDefaultSubobject<UBillboardComponent>(TEXT("PlayerSpawnPoint"));
	SetRootComponent(PlayerSpawnPoint);

	CheckpointTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("CheckpointTrigger"));
	CheckpointTrigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APlatformerCheckpoint::BeginPlay()
{
	Super::BeginPlay();

	CheckpointTrigger->OnComponentBeginOverlap.AddDynamic(this, &APlatformerCheckpoint::BeginCheckpointOverlap);
}

void APlatformerCheckpoint::BeginCheckpointOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APlatformerCharacter* PlayerCharacter = Cast<APlatformerCharacter>(OtherActor);

	if (PlayerCharacter)
	{
		PlayerCharacter->SetRespawnLocation(GetActorLocation());
	}

	UWorld* World = GetWorld();
	if (!World) return;

	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(World);
	if (!GameMode) return;

	APlatformerGameModeBase* PlatformerGameMode = Cast<APlatformerGameModeBase>(GameMode);
	if (!PlatformerGameMode) return;

	PlatformerGameMode->SetCurrentCheckpoint(this);
}

APlatformerChaser * APlatformerCheckpoint::GetCheckpointChaser()
{
	return CheckpointChaser;
}

