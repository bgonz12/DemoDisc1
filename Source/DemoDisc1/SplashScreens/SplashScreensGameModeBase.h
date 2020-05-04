// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoDisc1/DemoDisc1GameModeBase.h"
#include "SplashScreensGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEMODISC1_API ASplashScreensGameModeBase : public ADemoDisc1GameModeBase
{
	GENERATED_BODY()
	
protected:
	virtual void StartPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundMix* SilenceFadeSlow;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> SplashScreensUIClass;

	class USplashScreensUI* SplashScreensUI;

	FTimerHandle ChangeSplashScreenTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SplashScreenTime;

	FTimerHandle OpenLevelTimerHandle;

	FName LevelToOpen;

	void ChangeSplashScreen();

	void OpenLevel();

public:
	UFUNCTION(BlueprintCallable)
	virtual void QuitLevel() override;

	void ChangeLevel(FName LevelName);

	class USplashScreensUI* GetSplashScreensUI();
};
