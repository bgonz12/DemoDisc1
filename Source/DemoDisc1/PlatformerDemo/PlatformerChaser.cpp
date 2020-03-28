// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerChaser.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
//#include "ActorSequenceComponent.h"

#include "PlatformerCharacter.h"

// Sets default values
APlatformerChaser::APlatformerChaser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SetRootComponent(SplineComponent);

	StaticMeshContainer = CreateDefaultSubobject<USceneComponent>(TEXT("StaticMeshContainer"));
	StaticMeshContainer->SetupAttachment(RootComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(StaticMeshContainer);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);

	//BoulderFallSequence = CreateDefaultSubobject<UActorSequenceComponent>(TEXT("BoulderFallSequence"));

	MoveSpeed = 500.0f;

	BoulderRotateSpeed = 200.0f;
}

// Called when the game starts or when spawned
void APlatformerChaser::BeginPlay()
{
	Super::BeginPlay();
	
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &APlatformerChaser::BeginOverlap);

	EndLocation = SplineComponent->GetWorldLocationAtTime(SplineComponent->Duration);

	FRotator StartRotation = SplineComponent->GetRotationAtTime(0.0f, ESplineCoordinateSpace::World);
	StaticMeshContainer->SetWorldRotation(StartRotation);
}

// Called every frame
void APlatformerChaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsChasing)
	{
		FVector TargetLocation = StaticMeshContainer->GetComponentLocation() + GetActorForwardVector() * MoveSpeed * DeltaTime;

		FTransform FinalTransform = SplineComponent->FindTransformClosestToWorldLocation(TargetLocation, ESplineCoordinateSpace::World);
		StaticMeshContainer->SetWorldTransform(FinalTransform);

		StaticMesh->AddLocalRotation(FRotator(-BoulderRotateSpeed * DeltaTime, 0.0f, 0.0f));

		if (FVector::Dist(StaticMeshContainer->GetComponentLocation(), EndLocation) <= MoveSpeed * DeltaTime * 2.0f)
		{
			StopChasing();
		}
	}
}

void APlatformerChaser::StartChasing()
{
	//BoulderFallSequence
	bIsChasing = true;
}

void APlatformerChaser::StopChasing()
{
	bIsChasing = false;
}

void APlatformerChaser::BeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!bIsChasing && Cast<APlatformerCharacter>(OtherActor))
	{
		this->PlayStartAnimation();
	}
}

