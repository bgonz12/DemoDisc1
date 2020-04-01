// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlatformerGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FCollectibleCountUpdatedSignature, APlatformerGameModeBase, OnCollectibleCountUpdated, int, Value);

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
	FCollectibleCountUpdatedSignature OnCollectibleCountUpdated;

protected:
	class APlatformerCheckpoint* LastCheckpoint;

	class APlatformerCharacter* PlayerCharacter;

	FTimerHandle LoadCheckpointTimerHandle;

	bool bLoadingCheckpoint;

	int CollectibleCount;

	UFUNCTION()
	void LoadLastCheckpoint();

public:
	void TriggerLoadLastCheckpoint();

	void SetCurrentCheckpoint(class APlatformerCheckpoint* NewCheckpoint);

	void SetCollectibleCount(int Value);

	FORCEINLINE int GetCollectibleCount() { return CollectibleCount; };
};
