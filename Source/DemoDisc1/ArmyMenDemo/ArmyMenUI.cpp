// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenUI.h"
#include "Components/ProgressBar.h"

void UArmyMenUI::SetHealthBarPercent(float Value)
{
	HealthBar->SetPercent(Value);
}