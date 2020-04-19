// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameUI.generated.h"

/**
 * 
 */
UCLASS()
class DEMODISC1_API UEndGameUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

protected:
	UFUNCTION()
	void PhaseThreeAttack();

public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayCurtainFadeIn(float Delay);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayCurtainFadeOut(float Delay);
};
