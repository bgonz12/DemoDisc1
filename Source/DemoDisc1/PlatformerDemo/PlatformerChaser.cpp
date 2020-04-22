// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerChaser.h"
#include "Components/AudioComponent.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "PlatformerCharacter.h"
#include "PlatformerGameModeBase.h"
#include "DemoDisc1/SpookySwapComponent.h"

// Sets default values
APlatformerChaser::APlatformerChaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SetRootComponent(SplineComponent);

	ChaserContainer = CreateDefaultSubobject<USceneComponent>(TEXT("StaticMeshContainer"));
	ChaserContainer->SetupAttachment(RootComponent);

	BoulderMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoulderMesh"));
	BoulderMesh->SetupAttachment(ChaserContainer);

	BoulderAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("BoulderAudio"));
	BoulderAudio->SetupAttachment(BoulderMesh);

	SpookyLadyContainer = CreateDefaultSubobject<USceneComponent>(TEXT("SpookyLadyContainer"));
	SpookyLadyContainer->SetupAttachment(ChaserContainer);

	SpookyLadyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpookyLadyMesh"));
	SpookyLadyMesh->SetupAttachment(SpookyLadyContainer);

	KillSphere = CreateDefaultSubobject<USphereComponent>(TEXT("BoulderKillSphere"));
	KillSphere->SetupAttachment(ChaserContainer);

	ChaseTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	ChaseTriggerBox->SetupAttachment(RootComponent);

	SpookySwapComponent = CreateDefaultSubobject<USpookySwapComponent>(TEXT("SpookySwapComponent"));

	bShouldReset = true;

	bIsChasing = false;

	MoveSpeed = 600.0f;

	BoulderRotateSpeed = 200.0f;
}

// Called when the game starts or when spawned
void APlatformerChaser::BeginPlay()
{
	Super::BeginPlay();

	bShouldReset = true;

	bIsChasing = false;

	SpookySwapComponent->AddNormalComponent(BoulderMesh);
	SpookySwapComponent->AddSpookyComponent(SpookyLadyMesh);
	SpookySwapComponent->Initialize();

	DisableChaser();

	ChaseTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APlatformerChaser::BeginChaseTriggerOverlap);

	KillSphere->OnComponentBeginOverlap.AddDynamic(this, &APlatformerChaser::BeginBoulderOverlap);

	UWorld* World = GetWorld();
	
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();

		if (Controller)
		{
			PlayerActor = Controller->GetPawn();
		}
	}

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

		// Boulder rolling animation
		BoulderMesh->AddLocalRotation(FRotator(-BoulderRotateSpeed * DeltaTime, 0.0f, 0.0f));

		if (FVector::Dist(ChaserContainer->GetComponentLocation(), EndLocation) <= MoveSpeed * DeltaTime * 2.0f)
		{
			StopChasing();
		}

		if (PlayerActor && SpookySwapComponent->GetIsSpooky())
		{
			FVector LookAtStart = SpookyLadyContainer->GetComponentLocation();
			FVector LookAtEnd = PlayerActor->GetActorLocation();
			FRotator SpookyLadyRotation = UKismetMathLibrary::FindLookAtRotation(LookAtStart, LookAtEnd);

			SpookyLadyContainer->SetWorldRotation(SpookyLadyRotation);

			APlatformerCharacter* PlatformerCharacter = Cast<APlatformerCharacter>(PlayerActor);

			if (PlatformerCharacter && PlatformerCharacter->GetIsDead())
			{
				StopChasing();
			}
		}
	}
}

void APlatformerChaser::StartChasing()
{
	OnChaseStart.Broadcast();

	bIsChasing = true;
	this->PlayStartAnimation();
}

void APlatformerChaser::StopChasing()
{
	bIsChasing = false;
	this->PlayEndAnimation();
}

void APlatformerChaser::EnableChaser()
{
	if (!SpookySwapComponent->GetIsSpooky())
	{
		BoulderMesh->SetVisibility(true);
		BoulderMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
	else
	{
		SpookyLadyMesh->SetVisibility(true);
		SpookyLadyMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void APlatformerChaser::DisableChaser()
{
	if (!SpookySwapComponent->GetIsSpooky())
	{
		BoulderMesh->SetVisibility(false);
		BoulderMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		SpookyLadyMesh->SetVisibility(false);
		SpookyLadyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void APlatformerChaser::Reset()
{
	if (!bShouldReset) return;

	Super::Reset();

	StopChasing();
	DisableChaser();
	ChaserContainer->SetWorldLocation(StartLocation);
}

void APlatformerChaser::BeginChaseTriggerOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!bIsChasing && Cast<APlatformerCharacter>(OtherActor))
	{
		EnableChaser();
		StartChasing();
	}
}

void APlatformerChaser::BeginBoulderOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!bIsChasing) return;

	APlatformerCharacter* Player = Cast<APlatformerCharacter>(OtherActor);

	if (Player)
	{
		if (!SpookySwapComponent->GetIsSpooky())
		{
			Player->KillPlayer(EDeathAnimationType::SQUISH);
		}
		else
		{
			Player->KillPlayer(EDeathAnimationType::SPOOKY_LADY);
			bIsChasing = false;
		}
	}
}

