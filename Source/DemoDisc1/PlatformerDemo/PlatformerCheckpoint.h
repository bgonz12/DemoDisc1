// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformerCheckpoint.generated.h"

UCLASS()
class DEMODISC1_API APlatformerCheckpoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformerCheckpoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
	class UBillboardComponent* PlayerSpawnPoint;

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CheckpointTrigger;

	UPROPERTY(EditAnywhere)
	class APlatformerChaser* CheckpointChaser;

	UFUNCTION()
	void BeginCheckpointOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:
	class APlatformerChaser* GetCheckpointChaser();
};
