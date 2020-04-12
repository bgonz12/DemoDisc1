// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenPlayerController.h"

#include "ArmyMenCharacter.h"
#include "ArmyMenUI.h"

void AArmyMenPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameAndUI());
	bShowMouseCursor = false;

	if (ArmyMenUIClass)
	{
		ArmyMenUI = CreateWidget<UArmyMenUI>(this, ArmyMenUIClass);

		if (ArmyMenUI)
		{
			ArmyMenUI->AddToViewport();
		}
	}

	APawn* MyPawn = GetPawn();
	if (!MyPawn) return;

	AArmyMenCharacter* MyCharacter = Cast<AArmyMenCharacter>(MyPawn);
	if (!MyCharacter) return;

	MyCharacter->OnNotifyHealthChange.AddDynamic(this, &AArmyMenPlayerController::OnPawnNotifyHealthChange);
}

void AArmyMenPlayerController::OnPawnNotifyHealthChange()
{
	if (!ArmyMenUI) return;

	APawn* MyPawn = GetPawn();
	if (!MyPawn) return;

	AArmyMenCharacter* MyCharacter = Cast<AArmyMenCharacter>(MyPawn);
	if (!MyCharacter) return;

	float HealthPercent = (float) MyCharacter->GetCurrentHealth() / (float) MyCharacter->GetMaxHealth();

	ArmyMenUI->SetHealthBarPercent(HealthPercent);
}
