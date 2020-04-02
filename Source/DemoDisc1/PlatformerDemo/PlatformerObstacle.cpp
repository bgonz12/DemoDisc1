// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerObstacle.h"
#include "Components/StaticMeshComponent.h"

#include "PlatformerChaser.h"

// Sets default values
APlatformerObstacle::APlatformerObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);

	MeshContainer = CreateDefaultSubobject<USceneComponent>(TEXT("MeshContainer"));
	MeshContainer->SetupAttachment(RootComponent);

	NormalMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("NormalMesh"));
	NormalMesh->SetupAttachment(MeshContainer);

	SpookyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpookyMesh"));
	SpookyMesh->SetupAttachment(MeshContainer);

	bHasFallenOver = false;
}

// Called when the game starts or when spawned
void APlatformerObstacle::BeginPlay()
{
	Super::BeginPlay();

	bHasFallenOver = false;

	OnActorBeginOverlap.AddDynamic(this, &APlatformerObstacle::BeginOverlap);
}

void APlatformerObstacle::Reset()
{
	Super::Reset();

	bHasFallenOver = false;

	ResetFallOverAnimation();
}

void APlatformerObstacle::BeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	if (bHasFallenOver) return;

	APlatformerChaser* Chaser = Cast<APlatformerChaser>(OtherActor);

	if (Chaser)
	{
		bHasFallenOver = true;

		PlayFallOverAnimation();
	}
}

