// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerPlatform.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

#include "PlatformerDemo/PlatformerCharacter.h"

// Sets default values
APlatformerPlatform::APlatformerPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	SetRootComponent(Root);

	MeshContainer = CreateDefaultSubobject<USceneComponent>(TEXT("MeshContainer"));
	MeshContainer->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(MeshContainer);

	LandingTriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("LandingTriggerVolume"));
	LandingTriggerVolume->SetupAttachment(Root);

	bIsMovingPlatform = false;
	MoveSpeed = 0.0f;
}

// Called when the game starts or when spawned
void APlatformerPlatform::BeginPlay()
{
	Super::BeginPlay();

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

	if (MoveSpeed > 0.0f)
	{
		bIsMovingPlatform = true;
	}

	OnActorBeginOverlap.AddDynamic(this, &APlatformerPlatform::BeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &APlatformerPlatform::EndOverlap);
}

// Called every frame
void APlatformerPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsMovingPlatform)
	{
		FVector Location = GetActorLocation();
		float JourneyLength = FVector::Distance(GlobalStartLocation, GlobalTargetLocation);
		float JourneyTraveled = FVector::Distance(GlobalStartLocation, Location);

		if (JourneyTraveled >= JourneyLength)
		{
			FVector Swap = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = Swap;
		}

		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		Location += Direction * MoveSpeed * DeltaTime;
		SetActorLocation(Location);
	}
}

void APlatformerPlatform::BeginOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	APlatformerCharacter* Character = Cast<APlatformerCharacter>(OtherActor);

	if (Character)
	{
		PlayLandingAnimation();
	}
}

void APlatformerPlatform::EndOverlap(AActor * OverlappedActor, AActor * OtherActor)
{
	APlatformerCharacter* Character = Cast<APlatformerCharacter>(OtherActor);

	if (Character)
	{
		PlayDepartingAnimation();
	}
}

