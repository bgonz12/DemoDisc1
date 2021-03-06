// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerCharacterController.h"

#include "PlatformerUI.h"

APlatformerCharacterController::APlatformerCharacterController()
{
	// This needs to be done in order to stay focused on CameraSplineTrack after Reset
	bAutoManageActiveCameraTarget = false;
}

void APlatformerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;

	if (PlatformerUIClass)
	{
		PlatformerUI = CreateWidget<UPlatformerUI>(this, PlatformerUIClass);

		if (PlatformerUI)
		{
			PlatformerUI->AddToViewport();
		}
	}
}

UPlatformerUI* APlatformerCharacterController::GetPlatformerUI()
{
	return PlatformerUI;
}
