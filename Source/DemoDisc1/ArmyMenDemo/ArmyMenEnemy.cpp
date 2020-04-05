// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenEnemy.h"

// Sets default values
AArmyMenEnemy::AArmyMenEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AimTraceTypeQuery = ETraceTypeQuery::TraceTypeQuery3; // Player
}

// Called when the game starts or when spawned
void AArmyMenEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArmyMenEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AArmyMenEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

