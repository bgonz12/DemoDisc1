// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ArmyMenExplosiveBarrel.generated.h"

UCLASS()
class DEMODISC1_API AArmyMenExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AArmyMenExplosiveBarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Reset() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USceneComponent* MeshContainer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	int MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	int CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	bool bIsDead;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Explosion)
	class UParticleSystem* ExplosionParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Explosion)
	int ExplosionDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Explosion)
	int ExplosionRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Explosion)
	bool bDebugDrawRadius;

	void Kill();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
