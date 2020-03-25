// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraSplineTrack.h"
#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/SplineComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACameraSplineTrack::ACameraSplineTrack()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	SetRootComponent(SplineComponent);

	CameraContainer = CreateDefaultSubobject<USceneComponent>(TEXT("CameraContainer"));
	CameraContainer->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepWorldTransform);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Camera->AttachToComponent(CameraContainer, FAttachmentTransformRules::KeepRelativeTransform);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->AttachToComponent(SplineComponent, FAttachmentTransformRules::KeepWorldTransform);

	CameraLeadDistance = 700.0f;
}

// Called when the game starts or when spawned
void ACameraSplineTrack::BeginPlay()
{
	Super::BeginPlay();

	if (TargetActor == nullptr)
	{
		UWorld* World = GetWorld();
		if (!World) return;

		APlayerController* PlayerController = World->GetFirstPlayerController();
		if (!PlayerController) return;

		TargetActor = PlayerController->GetPawn();

		PlayerController->SetViewTarget(this);
	}
	
}

// Called every frame
void ACameraSplineTrack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!TargetActor) return;

	FVector TargetLocation = TargetActor->GetActorLocation();

	FTransform CameraTransform = SplineComponent->FindTransformClosestToWorldLocation(TargetLocation, ESplineCoordinateSpace::World);
	//CameraTransform.SetLocation(CameraTransform.GetLocation() + FVector(CameraLeadDistance, 0.0f, 0.0f));
	CameraContainer->SetWorldTransform(CameraTransform);
	CameraContainer->AddRelativeLocation(FVector(CameraLeadDistance, 0.0f, 0.0f));
}

