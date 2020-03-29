// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerCharacterController.h"

#include "PlatformerUI.h"

void APlatformerCharacterController::BeginPlay()
{
	Super::BeginPlay();

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
