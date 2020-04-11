// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "ArmyMenPlayerController.h"
#include "ArmyMenGameModeBase.h"

void AArmyMenPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	AController* MyController = GetController();
	if (!MyController) return;

	PlayerController = Cast<AArmyMenPlayerController>(MyController);
}

void AArmyMenPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator TargetRotation = GetActorRotation();
	;

	if (AimTarget)
	{
		FVector LookAtStart = GunMeshContainer->GetComponentLocation();
		FVector LookAtEnd = AimTarget->GetActorLocation();
		TargetRotation = UKismetMathLibrary::FindLookAtRotation(LookAtStart, LookAtEnd);

	}
	else
	{
		TargetRotation = GetActorRotation() + FRotator(0.0f, TurnInput * 15.0f, 0.0f);
	}

	FRotator GunRotation = FMath::Lerp(GunMeshContainer->GetComponentRotation(), TargetRotation, 8.0f * DeltaTime);

	GunMeshContainer->SetWorldRotation(GunRotation);
}

void AArmyMenPlayerCharacter::Reset()
{
	Super::Reset();

	if (!GetIsReloadable()) return;

	if (PlayerController)
	{
		PlayerController->Possess(this);

		EnableInput(PlayerController);
	}
}

void AArmyMenPlayerCharacter::Kill()
{
	if (bIsDead) return;

	Super::Kill();

	if (PlayerController)
	{
		DisableInput(PlayerController);

		/*UPlatformerUI* PlatformerUI = PlayerController->GetPlatformerUI();

		if (PlatformerUI)
		{
			PlatformerUI->PlayCurtainFadeOut();
		}*/
	}

	UWorld* World = GetWorld();
	if (!World) return;

	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(World);
	if (!GameMode) return;

	AArmyMenGameModeBase* PlatformerGameMode = Cast<AArmyMenGameModeBase>(GameMode);
	if (!PlatformerGameMode) return;

	PlatformerGameMode->TriggerLoadLastCheckpoint(3.0f);
}