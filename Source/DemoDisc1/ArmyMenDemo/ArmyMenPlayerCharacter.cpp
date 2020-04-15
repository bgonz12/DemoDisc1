// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "ArmyMenPlayerController.h"
#include "ArmyMenGameModeBase.h"
#include "DemoDisc1/SpookySwapStaticMeshComponent.h"

AArmyMenPlayerCharacter::AArmyMenPlayerCharacter()
{
	SilencerMesh = CreateDefaultSubobject<USpookySwapStaticMeshComponent>(TEXT("SilencerMesh"));
	SilencerMesh->SetupAttachment(GetMesh(), FName("SilencerSocket"));
}

void AArmyMenPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SilencerMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("SilencerSocket"));

	AController* MyController = GetController();
	if (!MyController) return;

	PlayerController = Cast<AArmyMenPlayerController>(MyController);
}

void AArmyMenPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator TargetRotation = GetActorRotation();

	if (AimTarget)
	{
		FVector LookAtStart = MeshContainer->GetComponentLocation();
		FVector LookAtEnd = AimTarget->GetActorLocation();
		TargetRotation = UKismetMathLibrary::FindLookAtRotation(LookAtStart, LookAtEnd);

	}
	else
	{
		TargetRotation = GetActorRotation() + FRotator(0.0f, TurnInput * 15.0f, 0.0f);
	}

	FRotator GunRotation = FMath::Lerp(MeshContainer->GetComponentRotation(), TargetRotation, 8.0f * DeltaTime);

	MeshContainer->SetWorldRotation(GunRotation);
}

void AArmyMenPlayerCharacter::Reset()
{
	if (!GetIsReloadable()) return;

	if (PlayerController)
	{
		PlayerController->Possess(this);

		EnableInput(PlayerController);
	}

	GetMesh()->SetVisibility(true);

	Super::Reset();
}

void AArmyMenPlayerCharacter::Kill()
{
	if (bIsDead) return;

	Super::Kill();

	if (PlayerController)
	{
		DisableInput(PlayerController);
	}

	GetMesh()->SetVisibility(false);

	UWorld* World = GetWorld();
	if (!World) return;

	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(World);
	if (!GameMode) return;

	AArmyMenGameModeBase* PlatformerGameMode = Cast<AArmyMenGameModeBase>(GameMode);
	if (!PlatformerGameMode) return;

	PlatformerGameMode->TriggerLoadLastCheckpoint(4.0f);
}