// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameUI.h"
#include "Kismet/GameplayStatics.h"

#include "EndGameGameModeBase.h"

bool UEndGameUI::Initialize()
{
	if (!Super::Initialize()) return false;

	PlayCurtainFadeIn(0.0f);

	UWorld* World = GetWorld();
	if (!World) return false;

	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(World);
	if (!GameMode) return false;

	AEndGameGameModeBase* EndGameGameMode = Cast<AEndGameGameModeBase>(GameMode);
	if (!EndGameGameMode) return false;

	EndGameGameMode->OnPhaseThreeAttack.AddDynamic(this, &UEndGameUI::PhaseThreeAttack);

	return true;
}

void UEndGameUI::PhaseThreeAttack()
{
	PlayCurtainFadeOut(0.0f);
}
