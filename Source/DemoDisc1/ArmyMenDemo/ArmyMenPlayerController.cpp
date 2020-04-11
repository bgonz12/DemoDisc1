// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenPlayerController.h"

void AArmyMenPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = false;
}