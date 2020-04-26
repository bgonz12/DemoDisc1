// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "ArmyMenTargetComponent.h"
#include "DemoDisc1/SpookyEnableActorComponent.h"

// Sets default values
AArmyMenExplosiveBarrel::AArmyMenExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpookyEnableActorComponent = CreateDefaultSubobject<USpookyEnableActorComponent>(TEXT("SpookyEnableActorComponent"));

	MeshContainer = CreateDefaultSubobject<USceneComponent>(TEXT("MeshContainer"));
	SetRootComponent(MeshContainer);

	TargetComponent = CreateDefaultSubobject<UArmyMenTargetComponent>(TEXT("TargetComponent"));
	TargetComponent->SetupAttachment(RootComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(MeshContainer);

	MaxHealth = 2;
	CurrentHealth = 0;

	ExplosionDamage = 5;
	ExplosionRadius = 300.0f;

	bDebugDrawRadius = false;
}

// Called when the game starts or when spawned
void AArmyMenExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
	bIsDead = false;

	CurrentHealth = MaxHealth;
}

void AArmyMenExplosiveBarrel::Reset()
{
	bIsDead = false;

	CurrentHealth = MaxHealth;

	StaticMesh->SetVisibility(true);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AArmyMenExplosiveBarrel::Kill()
{
	if (bIsDead) return;

	bIsDead = true;

	StaticMesh->SetVisibility(false);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	UGameplayStatics::ApplyRadialDamageWithFalloff(
		this,
		ExplosionDamage,
		ExplosionDamage,
		GetActorLocation(),
		ExplosionRadius,
		ExplosionRadius,
		0.0f,
		TSubclassOf<UDamageType>(UDamageType::StaticClass()),
		IgnoreActors,
		this);

	UWorld* World = GetWorld();
	if (!World) return;

	if (ExplosionParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(World, ExplosionParticle, GetActorTransform());
	}

	if (ExplosionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(World, ExplosionSound, GetActorLocation());
	}

	if (bDebugDrawRadius)
	{
		UKismetSystemLibrary::DrawDebugSphere
		(
			World,
			GetActorLocation(),
			ExplosionRadius,
			16,
			FLinearColor::Red,
			5.0f,
			1.0f
		);
	}
}

float AArmyMenExplosiveBarrel::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	int Damage = FMath::FloorToInt(DamageAmount);

	CurrentHealth -= Damage;

	if (CurrentHealth <= 0)
	{
		CurrentHealth = 0;

		Kill();
	}

	return DamageAmount;
}

