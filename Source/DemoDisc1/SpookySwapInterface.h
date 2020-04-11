// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SpookySwapInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USpookySwapInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEMODISC1_API ISpookySwapInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
	UFUNCTION()
	virtual void SwapToNormal() = 0;

	UFUNCTION()
	virtual void SwapToSpooky() = 0;
};
