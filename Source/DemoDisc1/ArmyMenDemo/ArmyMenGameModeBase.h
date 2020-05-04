// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DemoDisc1/DemoDisc1GameModeBase.h"
#include "DemoDisc1/LevelTransitioner.h"
#include "ArmyMenGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class DEMODISC1_API AArmyMenGameModeBase : public ADemoDisc1GameModeBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void QuitLevel() override;
};
