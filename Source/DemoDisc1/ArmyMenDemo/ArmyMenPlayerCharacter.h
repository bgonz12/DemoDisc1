// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArmyMenCharacter.h"
#include "ArmyMenPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DEMODISC1_API AArmyMenPlayerCharacter : public AArmyMenCharacter
{
	GENERATED_BODY()

public:
	virtual void Reset() override;

protected:
	virtual void Kill() override;

};
