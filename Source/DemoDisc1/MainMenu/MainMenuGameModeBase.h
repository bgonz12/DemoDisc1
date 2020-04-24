// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoDisc1/DemoDisc1GameModeBase.h"
#include "DemoDisc1/LevelTransitioner.h"
#include "MainMenuGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FChangeLevelSignature, AMainMenuGameModeBase, OnChangeLevel);

/**
 * 
 */
UCLASS()
class DEMODISC1_API AMainMenuGameModeBase : public ADemoDisc1GameModeBase, public ILevelTransitioner
{
	GENERATED_BODY()
	
protected:
	virtual void StartPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundMix* SilenceFadeSlow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> MainMenuUIClass;

	class UMainMenuUI* MainMenuUI;

	FTimerHandle OpenLevelTimerHandle;

	FName LevelToOpen;

	void OpenLevel();

public:
	FChangeLevelSignature OnChangeLevel;

	void TransitionToLevel(FName LevelName) override;

	void QuitLevel() override;

	class UMainMenuUI* GetMainMenuUI();
};
