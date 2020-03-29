// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerChaser.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

#include "PlatformerCharacter.h"
#include "PlatformerGameModeBase.h"

// Sets default values
APlatformerChaser::APlatformerChaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SetRootComponent(SplineComponent);

	ChaserContainer = CreateDefaultSubobject<USceneComponent>(TEXT("StaticMeshContainer"));
	ChaserContainer->SetupAttachment(RootComponent);

	BoulderStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoulderStaticMesh"));
	BoulderStaticMesh->SetupAttachment(ChaserContainer);

	BoulderKillSphere = CreateDefaultSubobject<USphereComponent>(TEXT("BoulderKillSphere"));
	BoulderKillSphere->SetupAttachment(BoulderStaticMesh);

	ChaseTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	ChaseTriggerBox->SetupAttachment(RootComponent);

	MoveSpeed = 600.0f;

	BoulderRotateSpeed = 200.0f;
}

// Called when the game starts or when spawned
void APlatformerChaser::BeginPlay()
{
	Super::BeginPlay();

	bIsChasing = false;
	DisableChaser();

	ChaseTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APlatformerChaser::BeginChaseTriggerOverlap);

	BoulderKillSphere->OnComponentBeginOverlap.AddDynamic(this, &APlatformerChaser::BeginBoulderOverlap);

	StartLocation = ChaserContainer->GetComponentLocation();
	EndLocation = SplineComponent->GetWorldLocationAtTime(SplineComponent->Duration);

	FRotator StartRotation = SplineComponent->GetRotationAtTime(0.0f, ESplineCoordinateSpace::World);
	ChaserContainer->SetWorldRotation(StartRotation);
}

// Called every frame
void APlatformerChaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsChasing)
	{
		FVector TargetLocation = ChaserContainer->GetComponentLocation() + GetActorForwardVector() * MoveSpeed * DeltaTime;

		FTransform FinalTransform = SplineComponent->FindTransformClosestToWorldLocation(TargetLocation, ESplineCoordinateSpace::World);
		ChaserContainer->SetWorldTransform(FinalTransform);

		BoulderStaticMesh->AddLocalRotation(FRotator(-BoulderRotateSpeed * DeltaTime, 0.0f, 0.0f));

		if (FVector::Dist(ChaserContainer->GetComponentLocation(), EndLocation) <= MoveSpeed * DeltaTime * 2.0f)
		{
			StopChasing();
		}
	}
}

void APlatformerChaser::StartChasing()
{
	bIsChasing = true;
}

void APlatformerChaser::StopChasing()
{
	bIsChasing = false;
}

void APlatformerChaser::EnableChaser()
{
	BoulderStaticMesh->SetVisibility(true);
	BoulderStaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void APlatformerChaser::DisableChaser()
{
	BoulderStaticMesh->SetVisibility(false);
	BoulderStaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APlatformerChaser::Reset()
{
	Super::Reset();

	bIsChasing = false;
	DisableChaser();
	ChaserContainer->SetWorldLocation(StartLocation);
}

void APlatformerChaser::BeginChaseTriggerOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!bIsChasing && Cast<APlatformerCharacter>(OtherActor))
	{
		EnableChaser();
		StartChasing();
		this->PlayStartAnimation();
	}
}

void APlatformerChaser::BeginBoulderOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!bIsChasing) return;

	APlatformerCharacter* Player = Cast<APlatformerCharacter>(OtherActor);

	if (Player)
	{
		Player->KillPlayer(DeathAnimationType::SQUISH);
	}
}

