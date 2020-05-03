// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoPickupSphereComponent.h"

#include "ArmyMenPlayerCharacter.h"

void UAmmoPickupSphereComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UAmmoPickupSphereComponent::BeginOverlap);

	DisablePickup();
}

void UAmmoPickupSphereComponent::BeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AArmyMenPlayerCharacter* Player = Cast<AArmyMenPlayerCharacter>(OtherActor);
	if (!Player) return;

	int Ammo = (int) FMath::FRandRange(MinAmmo, MaxAmmo + 1);

	Player->ReceiveAmmo(Ammo);

	UE_LOG(LogTemp, Warning, TEXT("Player got ammo!"));

	DisablePickup();
}

void UAmmoPickupSphereComponent::EnablePickup()
{
	SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}


void UAmmoPickupSphereComponent::DisablePickup()
{
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
