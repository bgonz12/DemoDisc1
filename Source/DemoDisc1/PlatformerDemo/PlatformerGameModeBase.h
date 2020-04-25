// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoDisc1/DemoDisc1GameModeBase.h"
#include "DemoDisc1/LevelTransitioner.h"
#include "PlatformerGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE_OneParam(FCollectibleCountUpdatedSignature, APlatformerGameModeBase, OnCollectibleCountUpdated, int, Value);

/**
 * 
 */
UCLASS()
class DEMODISC1_API APlatformerGameModeBase : public ADemoDisc1GameModeBase
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;

protected:
	int CollectibleCount;

public:
	FCollectibleCountUpdatedSignature OnCollectibleCountUpdated;
	
	virtual void QuitLevel() override;

	/** Getters **/
	FORCEINLINE int GetCollectibleCount() { return CollectibleCount; };

	/** Setters **/
	void SetCollectibleCount(int Value);
};
