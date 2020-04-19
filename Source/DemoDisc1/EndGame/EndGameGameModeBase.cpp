// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameGameModeBase.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"

void AEndGameGameModeBase::StartPlay()
{
	Super::StartPlay();

	UWorld* World = GetWorld();
	if (!World) return;

	World->GetTimerManager().ClearTimer(PhaseOneAttackTimerHandle);
	World->GetTimerManager().SetTimer(PhaseOneAttackTimerHandle, this, &AEndGameGameModeBase::PhaseOneAttack, PhaseOneAttackTriggerTime, false);
}

void AEndGameGameModeBase::PhaseOneAttack()
{
	OnPhaseOneAttack.Broadcast();

	UWorld* World = GetWorld();
	if (!World) return;

	World->GetTimerManager().ClearTimer(PhaseTwoAttackTimerHandle);
	World->GetTimerManager().SetTimer(PhaseTwoAttackTimerHandle, this, &AEndGameGameModeBase::PhaseTwoAttack, PhaseTwoAttackTriggerTime, false);
}

void AEndGameGameModeBase::PhaseTwoAttack()
{
	OnPhaseTwoAttack.Broadcast();

	UWorld* World = GetWorld();
	if (!World) return;

	World->GetTimerManager().ClearTimer(PhaseThreeAttackTimerHandle);
	World->GetTimerManager().SetTimer(PhaseThreeAttackTimerHandle, this, &AEndGameGameModeBase::PhaseThreeAttack, PhaseThreeAttackTriggerTime, false);

}

void AEndGameGameModeBase::PhaseThreeAttack()
{
	OnPhaseThreeAttack.Broadcast();

	UWorld* World = GetWorld();
	if (!World) return;

	World->GetTimerManager().ClearTimer(EndGameTimerHandle);
	World->GetTimerManager().SetTimer(EndGameTimerHandle, this, &AEndGameGameModeBase::EndGame, EndGameTriggerTime, false);
}

void AEndGameGameModeBase::EndGame()
{
	OnEndGame.Broadcast();

	FGenericPlatformMisc::RequestExit(false);
}