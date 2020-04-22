// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SplashScreensUI.generated.h"

/**
 * 
 */
UCLASS()
class DEMODISC1_API USplashScreensUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(Meta = (BindWidget))
	class UWidgetSwitcher* NormalSplashScreenSwitcher;

	UPROPERTY(Meta = (BindWidget))
	class UWidgetSwitcher* SpookySplashScreenSwitcher;

	UPROPERTY(BlueprintReadWrite)
	class UWidgetSwitcher* TargetWidgetSwitcher;

	bool bIsSpooky;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayFadeInAnimation();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void PlayFadeOutAnimation();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void ChangeSplashScreen(int SplashScreenIndex);

	int GetCurrentSplashScreenIndex();

	int GetNumSplashScreens();

	//void SetIsSpooky(bool IsSpooky);
};
