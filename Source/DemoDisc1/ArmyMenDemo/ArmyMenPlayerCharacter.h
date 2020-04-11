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

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void Reset() override;

protected:
	class AArmyMenPlayerController* PlayerController;

	virtual void Kill() override;

};
