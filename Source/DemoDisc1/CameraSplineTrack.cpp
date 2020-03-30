// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraSplineTrack.h"
#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/SplineComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACameraSplineTrack::ACameraSplineTrack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SetRootComponent(SplineComponent);

	CameraContainer = CreateDefaultSubobject<USceneComponent>(TEXT("CameraContainer"));
	CameraContainer->SetupAttachment(SplineComponent);

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(CameraContainer);
	CameraBoom->TargetArmLength = 300.0f; // The camera leads at this distance ahead of the character

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Camera->SetupAttachment(CameraBoom);
}

// Called when the game starts or when spawned
void ACameraSplineTrack::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (!World) return;

	PlayerController = World->GetFirstPlayerController();
	if (!PlayerController) return;

	PlayerController->SetViewTarget(this);

	if (TargetActor == nullptr)
	{
		TargetActor = PlayerController->GetPawn();
	}
}

// Called every frame
void ACameraSplineTrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TargetActor) return;

	FVector TargetLocation = TargetActor->GetActorLocation();

	FTransform CameraTransform = SplineComponent->FindTransformClosestToWorldLocation(TargetLocation, ESplineCoordinateSpace::World);
	CameraContainer->SetWorldTransform(CameraTransform);
}

void ACameraSplineTrack::Reset()
{
	Super::Reset();

	if (PlayerController && PlayerController->GetViewTarget() != this)
	{
		PlayerController->SetViewTarget(this);
	}
}

