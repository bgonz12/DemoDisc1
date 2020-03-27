// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformerChaser.generated.h"

UCLASS()
class DEMODISC1_API APlatformerChaser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformerChaser();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	bool bIsChasing;

	UPROPERTY(EditAnywhere)
	float MoveSpeed;

	UPROPERTY(EditAnywhere)
	float BoulderRotateSpeed;

protected:
	UPROPERTY(VisibleAnywhere)
	class USceneComponent* StaticMeshContainer;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere)
	class USplineComponent* SplineComponent;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerBox;

	//UPROPERTY(VisibleAnywhere)
	//class UActorSequenceComponent* BoulderFallSequence;

	FVector EndLocation;

	void StartChasing();

	void StopChasing();

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
};
