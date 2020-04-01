// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlatformerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEMODISC1_API APlatformerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void StartPlay() override;

public:
	void TriggerLoadLastCheckpoint();

protected:
	class APlatformerCheckpoint* LastCheckpoint;

	class APlatformerCharacter* PlayerCharacter;

	FTimerHandle LoadCheckpointTimerHandle;

	bool bLoadingCheckpoint;

	int CollectibleCounter;

	UFUNCTION()
	void LoadLastCheckpoint();

public:
	void SetCurrentCheckpoint(class APlatformerCheckpoint* NewCheckpoint);

	void SetCollectibleCounter(int Value);

	FORCEINLINE int GetCollectibleCounter() { return CollectibleCounter; };
};
