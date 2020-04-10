// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraSplineTrack.generated.h"

UCLASS()
class DEMODISC1_API ACameraSplineTrack : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACameraSplineTrack();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Reset() override;

protected:
	UPROPERTY(EditAnywhere)
	AActor* TargetActor;

	UPROPERTY(EditAnywhere)
	class APlayerController* PlayerController;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* CameraBoomContainer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	class USceneComponent* CameraContainer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	class UDutchAngleCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	class USplineComponent* SplineComponent;
};
