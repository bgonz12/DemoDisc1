// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGamePlayerCharacterController.h"

#include "EndGameUI.h"

AEndGamePlayerCharacterController::AEndGamePlayerCharacterController()
{

}

void AEndGamePlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = false;

	if (EndGameUIClass)
	{
		EndGameUI = CreateWidget<UEndGameUI>(this, EndGameUIClass);

		if (EndGameUI)
		{
			EndGameUI->AddToViewport();
		}
	}
}

UEndGameUI* AEndGamePlayerCharacterController::GetEndGameUI()
{
	return EndGameUI;
}
