// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGamePlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/AudioComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "EndGameGameModeBase.h"

// Sets default values
AEndGamePlayerCharacter::AEndGamePlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// set our turn rates for input
	BaseTurnRate = 90.0f;
	BaseLookUpRate = 90.0f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	PTSDAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("PTSDAudio"));
	PTSDAudio->SetupAttachment(GetCapsuleComponent());
}

// Called when the game starts or when spawned
void AEndGamePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	UWorld* World = GetWorld();
	if (!World) return;

	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(World);
	if (!GameMode) return;

	AEndGameGameModeBase* EndGameGameMode = Cast<AEndGameGameModeBase>(GameMode);
	if (!EndGameGameMode) return;

	EndGameGameMode->OnPhaseOneAttack.AddDynamic(this, &AEndGamePlayerCharacter::PhaseOneAttack);
	EndGameGameMode->OnPhaseTwoAttack.AddDynamic(this, &AEndGamePlayerCharacter::PhaseTwoAttack);
	EndGameGameMode->OnPhaseThreeAttack.AddDynamic(this, &AEndGamePlayerCharacter::PhaseThreeAttack);
	EndGameGameMode->OnEndGame.AddDynamic(this, &AEndGamePlayerCharacter::EndGame);
}

// Called to bind functionality to input
void AEndGamePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AEndGamePlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEndGamePlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AEndGamePlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &AEndGamePlayerCharacter::LookUp);
}

void AEndGamePlayerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AEndGamePlayerCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AEndGamePlayerCharacter::Turn(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AEndGamePlayerCharacter::LookUp(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

