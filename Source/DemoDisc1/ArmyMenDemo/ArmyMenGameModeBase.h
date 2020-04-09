// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArmyMenGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEMODISC1_API AArmyMenGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void StartPlay() override;

protected:
	FTimerHandle LoadCheckpointTimerHandle;

	bool bLoadingCheckpoint;

	int CollectibleCount;

	UFUNCTION()
	void LoadLastCheckpoint();

public:
	void TriggerLoadLastCheckpoint(float Delay = 0.0f);
};
