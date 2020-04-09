// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "ArmyMenCheckpoint.generated.h"

/**
 * 
 */
UCLASS()
class DEMODISC1_API AArmyMenCheckpoint : public ATriggerBox
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AArmyMenCheckpoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> ReloadableActorsToDisable;

	UFUNCTION()
	void BeginOverlap(AActor * OverlappedActor, AActor * OtherActor);
};
