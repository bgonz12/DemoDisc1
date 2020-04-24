// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "LevelTransitioner.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class ULevelTransitioner : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEMODISC1_API ILevelTransitioner
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void TransitionToLevel(FName LevelName) = 0;

	virtual void QuitLevel() = 0;
};
