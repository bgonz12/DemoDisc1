// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AArmyMenProjectile::AArmyMenProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

// Called when the game starts or when spawned
void AArmyMenProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArmyMenProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

