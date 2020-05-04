// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoDisc1/DemoDisc1GameModeBase.h"
#include "DemoDisc1/LevelTransitioner.h"
#include "MainMenuGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEMODISC1_API AMainMenuGameModeBase : public ADemoDisc1GameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void StartPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> MainMenuUIClass;

	class UMainMenuUI* MainMenuUI;

public:
	virtual void TransitionToLevel(FName LevelName) override;

	UFUNCTION(BlueprintCallable)
	virtual void QuitLevel() override;

	UFUNCTION(BlueprintCallable)
	class UMainMenuUI* GetMainMenuUI();
};
