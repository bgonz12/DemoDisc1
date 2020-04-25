// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArmyMenEnemy.h"
#include "ArmyMenZombieSoldier.generated.h"

/**
 * 
 */
UCLASS()
class DEMODISC1_API AArmyMenZombieSoldier : public AArmyMenEnemy
{
	GENERATED_BODY()

public:
	virtual void Reset() override;

protected:
	FTimerHandle SpawnCrawlerTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AArmyMenCrawlerCharacter> CrawlerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CrawlerVisionDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bHasCrawlerSpawned;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector CrawlerSpawnLocation;
	
public:
	UFUNCTION()
	void SpawnCrawler();

	/** Getters **/
	FORCEINLINE float GetCrawlerVisionDistance() { return CrawlerVisionDistance; }

	FORCEINLINE bool GetHasCrawlerSpawned() { return bHasCrawlerSpawned; }
};
