// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MusicManager.h"
#include "PlatformerMusicManager.generated.h"

/**
 * 
 */
UCLASS()
class DEMODISC1_API APlatformerMusicManager : public AMusicManager
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
	class APlatformerChaser* MusicTransitionChaser;

	float ChaseValue;

	float TargetChaseValue;

	UFUNCTION(BlueprintCallable)
	void TransitionToChase();
};
