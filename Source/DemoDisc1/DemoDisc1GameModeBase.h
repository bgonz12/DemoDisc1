// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DemoDisc1GameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FPlayerDeathSignature, ADemoDisc1GameModeBase, OnPlayerDeath);

/**
 * 
 */
UCLASS()
class DEMODISC1_API ADemoDisc1GameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	

protected:
	virtual void StartPlay() override;

public:
	FPlayerDeathSignature OnPlayerDeath;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundMix* NormalSoundMix;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundMix* SpookySoundMix;

	FTimerHandle LoadCheckpointTimerHandle;

	bool bLoadingCheckpoint;

	UFUNCTION()
	void LoadLastCheckpoint();

public:
	void TriggerLoadLastCheckpoint(float Delay = 0.0f);
};
