// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ReloadableActor.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UReloadableActor : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class DEMODISC1_API IReloadableActor
{
	GENERATED_BODY()

private:
	bool bIsReloadable = true;

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	FORCEINLINE bool GetIsReloadable() { return bIsReloadable;  }

	FORCEINLINE void SetIsReloadable(bool IsReloadable) { bIsReloadable = IsReloadable; }
};
