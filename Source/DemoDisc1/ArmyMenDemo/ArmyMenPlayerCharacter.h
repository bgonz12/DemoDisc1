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
	AArmyMenPlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void Reset() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USpookySwapStaticMeshComponent* SilencerMesh;

	class AArmyMenPlayerController* PlayerController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float GunAimLerpSpeed;

	virtual void Kill() override;

};
