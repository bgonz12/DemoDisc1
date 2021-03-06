// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ArmyMenCharacter.h"
#include "ArmyMenEnemy.generated.h"

UCLASS()
class DEMODISC1_API AArmyMenEnemy : public AArmyMenCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AArmyMenEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Senses)
	float VisionDistance;

	virtual void Kill() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

public:
	FORCEINLINE float GetVisionDistance() { return VisionDistance; }
};
