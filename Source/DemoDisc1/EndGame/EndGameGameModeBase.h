// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EndGameGameModeBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FPhaseOneAttackSignature, AEndGameGameModeBase, OnPhaseOneAttack);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FPhaseTwoAttackSignature, AEndGameGameModeBase, OnPhaseTwoAttack);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FPhaseThreeAttackSignature, AEndGameGameModeBase, OnPhaseThreeAttack);
DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FEndGameSignature, AEndGameGameModeBase, OnEndGame);

/**
 * 
 */
UCLASS()
class DEMODISC1_API AEndGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	virtual void StartPlay() override;

public:
	FPhaseOneAttackSignature OnPhaseOneAttack;
	FPhaseTwoAttackSignature OnPhaseTwoAttack;
	FPhaseThreeAttackSignature OnPhaseThreeAttack;
	FEndGameSignature OnEndGame;

protected:
	FTimerHandle PhaseOneAttackTimerHandle;
	FTimerHandle PhaseTwoAttackTimerHandle;
	FTimerHandle PhaseThreeAttackTimerHandle;
	FTimerHandle EndGameTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundMix* SilenceFadeSoundMix;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PhaseOneAttackTriggerTime = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PhaseTwoAttackTriggerTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PhaseThreeAttackTriggerTime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EndGameTriggerTime = 5.0f;

	void PhaseOneAttack();
	void PhaseTwoAttack();
	void PhaseThreeAttack();
	void EndGame();
};
