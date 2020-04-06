// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenPlayerCharacter.h"

#include "ArmyMenPlayerController.h"

void AArmyMenPlayerCharacter::Reset()
{
	Super::Reset();

	AController* MyController = GetController();
	if (!MyController) return;

	AArmyMenPlayerController* PlayerController = Cast<AArmyMenPlayerController>(MyController);

	EnableInput(PlayerController);
}

void AArmyMenPlayerCharacter::Kill()
{
	if (bIsDead) return;

	Super::Kill();

	AController* MyController = GetController();
	if (!MyController) return;

	AArmyMenPlayerController* PlayerController = Cast<AArmyMenPlayerController>(MyController);

	DisableInput(PlayerController);
}