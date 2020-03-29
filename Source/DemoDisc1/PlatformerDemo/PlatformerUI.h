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

public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayCurtainFadeIn();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayCurtainFadeOut();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayShowCollectables();
};
