// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlatformerUI.generated.h"

/**
 * 
 */
UCLASS()
class DEMODISC1_API UPlatformerUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CollectibleText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CollectibleCounter;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayCurtainFadeIn(float Delay);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayCurtainFadeOut(float Delay);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayShowCollectables();

	int GetCollectibleCounter();

	UFUNCTION()
	void SetCollectibleCounter(int Value);
};
