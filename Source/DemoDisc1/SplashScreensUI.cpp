// Fill out your copyright notice in the Description page of Project Settings.


#include "SplashScreensUI.h"
#include "Components/WidgetSwitcher.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "DemoDisc1/DemoDisc1GameInstance.h"

bool USplashScreensUI::Initialize()
{
	if (!Super::Initialize()) return false;

	// Set NormalSplashScreenSwitcher to be the default TargetWidgetSwitcher
	TargetWidgetSwitcher = NormalSplashScreenSwitcher;

	UWorld* World = GetWorld();
	if (!World) return false;

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(World);
	if (!GameInstance) return false;

	UDemoDisc1GameInstance* DD1GameInstance = Cast<UDemoDisc1GameInstance>(GameInstance);
	if (!DD1GameInstance) return false;

	if (!DD1GameInstance->GetHasSpookyTransitioned())
	{
		NormalSplashScreenSwitcher->SetVisibility(ESlateVisibility::Visible);
		SpookySplashScreenSwitcher->SetVisibility(ESlateVisibility::Hidden);

		TargetWidgetSwitcher = NormalSplashScreenSwitcher;
	}
	else
	{
		SpookySplashScreenSwitcher->SetVisibility(ESlateVisibility::Visible);
		NormalSplashScreenSwitcher->SetVisibility(ESlateVisibility::Hidden);

		TargetWidgetSwitcher = SpookySplashScreenSwitcher;
	}

	return true;
}

int USplashScreensUI::GetCurrentSplashScreenIndex()
{
	return TargetWidgetSwitcher->GetActiveWidgetIndex();
}

int USplashScreensUI::GetNumSplashScreens()
{
	return TargetWidgetSwitcher->GetNumWidgets();
}
