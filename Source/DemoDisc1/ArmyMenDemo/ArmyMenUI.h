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

public:
	virtual bool Initialize() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UImage* DeathCurtain;

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterialInterface* DeathCurtainMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class UDemoDisc1GameInstance* DemoDisc1GameInstance;

	bool bCharacterIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DeathCurtainTime = 3.0f;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayTakeDamageAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayCurtainFadeIn(float Delay);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayCurtainFadeOut(float Delay);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayEndLevelCurtainFadeOut();

public:
	UFUNCTION()
	void SetHealthBarPercent(float Value);
};
