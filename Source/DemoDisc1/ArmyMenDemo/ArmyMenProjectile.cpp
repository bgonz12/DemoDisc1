// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AArmyMenProjectile::AArmyMenProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMesh);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->ProjectileGravityScale = 0.0f;

	Damage = 1.0f;
}

// Called when the game starts or when spawned
void AArmyMenProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		StaticMesh->IgnoreActorWhenMoving(MyOwner, true);
	}

	OnActorHit.AddDynamic(this, &AArmyMenProjectile::ActorHit);
}

// Called every frame
void AArmyMenProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AArmyMenProjectile::ActorHit(AActor * SelfActor, AActor * OtherActor, FVector NormalImpulse, const FHitResult & Hit)
{
	// Create a damage event  
	TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
	FDamageEvent DamageEvent(ValidDamageTypeClass);

	OtherActor->TakeDamage(Damage, DamageEvent, GetInstigatorController(), this);

	Destroy();
}

