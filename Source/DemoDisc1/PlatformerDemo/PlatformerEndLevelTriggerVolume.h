// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "PlatformerEndLevelTriggerVolume.generated.h"

/**
 * 
 */
UCLASS()
class DEMODISC1_API APlatformerEndLevelTriggerVolume : public ATriggerVolume
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UFUNCTION()
	void BeginOverlap(AActor * OverlappedActor, AActor * OtherActor);
};
