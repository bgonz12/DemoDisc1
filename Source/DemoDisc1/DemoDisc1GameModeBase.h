// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LevelTransitioner.h"
#include "DemoDisc1GameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FLoadCheckpointTriggeredSignature, ADemoDisc1GameModeBase, OnLoadCheckpointTriggered);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FTransitionToLevelSignature, ADemoDisc1GameModeBase, OnTransitionToLevel);

/**
 * 
 */
UCLASS()
class DEMODISC1_API ADemoDisc1GameModeBase : public AGameModeBase, public ILevelTransitioner
{
	GENERATED_BODY()
	

protected:
	virtual void StartPlay() override;

public:
	FLoadCheckpointTriggeredSignature OnLoadCheckpointTriggered;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterialParameterCollection* GlobalMaterialParamCollection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundMix* NormalSoundMix;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundMix* SpookySoundMix;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundMix* LevelFadeOutSoundMix;

	FTimerHandle LoadCheckpointTimerHandle;

	bool bLoadingCheckpoint;

	FTimerHandle OpenLevelTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LevelTransitionTime = 1.0f;

	FName LevelToOpen;

	bool bIsTransitioningLevel;

	UFUNCTION()
	void LoadCheckpoint();

	UFUNCTION()
	void OpenLevel();

public:
	FTransitionToLevelSignature OnTransitionToLevel;

	virtual void TransitionToLevel(FName LevelName) override;

	virtual void QuitLevel() override;

	void TriggerLoadCheckpoint(float Delay = 0.0f);
};
