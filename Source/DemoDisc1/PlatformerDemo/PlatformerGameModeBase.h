// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoDisc1/DemoDisc1GameModeBase.h"
#include "DemoDisc1/LevelTransitioner.h"
#include "PlatformerGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FTransitionToLevelSignature, APlatformerGameModeBase, OnTransitionToLevel);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FCollectibleCountUpdatedSignature, APlatformerGameModeBase, OnCollectibleCountUpdated, int, Value);

/**
 * 
 */
UCLASS()
class DEMODISC1_API APlatformerGameModeBase : public ADemoDisc1GameModeBase, public ILevelTransitioner
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundMix* SilenceFadeSlow;

	FTimerHandle OpenLevelTimerHandle;

	FName LevelToOpen;

	int CollectibleCount;

	void OpenLevel();

public:
	FTransitionToLevelSignature OnTransitionToLevel;
	FCollectibleCountUpdatedSignature OnCollectibleCountUpdated;

	void TransitionToLevel(FName LevelName) override;
	
	void QuitLevel() override;

	/** Getters **/
	FORCEINLINE int GetCollectibleCount() { return CollectibleCount; };

	/** Setters **/
	void SetCollectibleCount(int Value);
};
