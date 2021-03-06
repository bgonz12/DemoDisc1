// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DemoDisc1GameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FSpookyTransitionSignature, UDemoDisc1GameInstance, OnSpookyTransition);

/**
 * 
 */
UCLASS()
class DEMODISC1_API UDemoDisc1GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UDemoDisc1GameInstance();

	FSpookyTransitionSignature OnSpookyTransition;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundMix* NormalSoundMix;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundMix* SpookySoundMix;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterialParameterCollection* GlobalMaterialParamCollection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LevelsCompleted;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int LevelsCompletedToTransition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHasSpookyTransitioned;

public:
	void CompleteLevel();

	void TriggerSpookyTransition();

	bool GetIsTransitionTime();

	UFUNCTION(BlueprintCallable)
	bool GetHasSpookyTransitioned();
};
