// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ArmyMenUI.generated.h"

/**
 * 
 */
UCLASS()
class DEMODISC1_API UArmyMenUI : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

public:
	UFUNCTION()
	void SetHealthBarPercent(float Value);
};
