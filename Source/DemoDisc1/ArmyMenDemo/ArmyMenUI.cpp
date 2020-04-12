// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenUI.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Materials/MaterialInstanceDynamic.h"

bool UArmyMenUI::Initialize()
{
	if (!Super::Initialize()) return false;

	DeathCurtain->SetBrushFromMaterial(DeathCurtainMaterial);

	DeathCurtain->GetDynamicMaterial()->SetScalarParameterValue(FName("Cutoff"), 0.0f);

	return true;
}

void UArmyMenUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bCharacterIsDead)
	{
		float DeathCurtainCutoff;
		DeathCurtain->GetDynamicMaterial()->GetScalarParameterValue(FName("Cutoff"), DeathCurtainCutoff);

		DeathCurtain->GetDynamicMaterial()->SetScalarParameterValue(FName("Cutoff"), DeathCurtainCutoff + InDeltaTime / DeathCurtainTime);
	}
}

void UArmyMenUI::SetHealthBarPercent(float Value)
{
	if (Value <= 0.0f)
	{
		bCharacterIsDead = true;
	}
	else if(bCharacterIsDead)
	{
		bCharacterIsDead = false;

		DeathCurtain->GetDynamicMaterial()->SetScalarParameterValue(FName("Cutoff"), 0.0f);
	}

	if (HealthBar->Percent > Value)
	{
		PlayTakeDamageAnimation();
	}

	HealthBar->SetPercent(Value);
}