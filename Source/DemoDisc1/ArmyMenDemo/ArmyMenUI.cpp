// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenUI.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "DemoDisc1/DemoDisc1GameInstance.h"

bool UArmyMenUI::Initialize()
{
	if (!Super::Initialize()) return false;

	DeathCurtain->SetBrushFromMaterial(DeathCurtainMaterial);

	DeathCurtain->GetDynamicMaterial()->SetScalarParameterValue(FName("Cutoff"), 0.0f);

	PlayFadeInAnimation(0.0f);

	UWorld* World = GetWorld();
	if (!World) return false;

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(World);
	if (!GameInstance) return false;

	DemoDisc1GameInstance = Cast<UDemoDisc1GameInstance>(GameInstance);
	if (!DemoDisc1GameInstance) return false;

	return true;
}

void UArmyMenUI::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (bCharacterIsDead && !DemoDisc1GameInstance->GetHasSpookyTransitioned())
	{
		float DeathCurtainCutoff;
		DeathCurtain->GetDynamicMaterial()->GetScalarParameterValue(FName("Cutoff"), DeathCurtainCutoff);

		DeathCurtain->GetDynamicMaterial()->SetScalarParameterValue(FName("Cutoff"), DeathCurtainCutoff + InDeltaTime / DeathCurtainTime);
	}
}

void UArmyMenUI::SetHealthBarPercent(float Value)
{
	if (bCharacterIsDead)
	{
		// Check if health update makes character alive
		if (Value > 0.0f)
		{
			PlayFadeInAnimation(0.0f);

			bCharacterIsDead = false;

			DeathCurtain->GetDynamicMaterial()->SetScalarParameterValue(FName("Cutoff"), 0.0f);
		}
	}
	else
	{
		if (Value <= 0.0f)
		{
			if (!DemoDisc1GameInstance->GetHasSpookyTransitioned())
			{
				PlayFadeOutAnimation(2.5f);
			}
			else
			{
				PlayFadeOutAnimation(0.0f);
			}

			bCharacterIsDead = true;
		}
	}

	if (HealthBar->Percent > Value)
	{
		PlayTakeDamageAnimation();
	}

	HealthBar->SetPercent(Value);
}