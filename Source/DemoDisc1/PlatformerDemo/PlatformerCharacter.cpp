// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

#include "PlatformerCharacterController.h"
#include "PlatformerChaser.h"
#include "PlatformerGameModeBase.h"
#include "PlatformerUI.h"

// Sets default values
APlatformerCharacter::APlatformerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	CharacterCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CharacterCamera"));
	CharacterCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	CharacterCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	JumpGravity = 1.0f;
	FallGravity = 2.5f;
}

// Called when the game starts or when spawned
void APlatformerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (Controller != nullptr)
	{
		PlayerController = Cast<APlatformerCharacterController>(Controller);
	}

	RespawnTransform = GetActorTransform();

	bIsDead = false;
}

// Called every frame
void APlatformerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector CurrentVelocity = GetVelocity();
	if (CurrentVelocity.Z < -1.0f)
	{
		GetCharacterMovement()->GravityScale = FallGravity;
	}
}

// Called to bind functionality to input
void APlatformerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlatformerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlatformerCharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlatformerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlatformerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlatformerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlatformerCharacter::LookUpAtRate);
}

void APlatformerCharacter::KillPlayer(DeathAnimationType AnimType)
{
	if (bIsDead) return;

	bIsDead = true;

	if (PlayerController)
	{
		DisableInput(PlayerController);

		UPlatformerUI* PlatformerUI = PlayerController->GetPlatformerUI();

		if (PlatformerUI)
		{
			PlatformerUI->PlayCurtainFadeOut();
		}
	}

	PlayPlayerDeathAnimation(AnimType);

	UWorld* World = GetWorld();
	if (!World) return;

	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(World);
	if (!GameMode) return;

	APlatformerGameModeBase* PlatformerGameMode = Cast<APlatformerGameModeBase>(GameMode);
	if (!PlatformerGameMode) return;

	PlatformerGameMode->TriggerLoadLastCheckpoint(3.0f);
}

void APlatformerCharacter::Reset()
{
	// We do not call reset on parent class because doing so Destroys the actor 
	//Super::Reset();

	SetActorTransform(RespawnTransform);

	bIsDead = false;

	ResetPlayerDeathAnimation();

	if (PlayerController)
	{
		PlayerController->Possess(this);

		EnableInput(PlayerController);
		
		UPlatformerUI* PlatformerUI = PlayerController->GetPlatformerUI();

		if (PlatformerUI)
		{
			PlatformerUI->PlayCurtainFadeIn();
		}
	}
}

void APlatformerCharacter::Jump()
{
	Super::Jump();

	GetCharacterMovement()->GravityScale = JumpGravity;
}

void APlatformerCharacter::StopJumping()
{
	Super::StopJumping();

	GetCharacterMovement()->GravityScale = FallGravity;
}

void APlatformerCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlatformerCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlatformerCharacter::MoveForward(float Value)
{
	if ((PlayerController != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APlatformerCharacter::MoveRight(float Value)
{
	if ((PlayerController != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = PlayerController->PlayerCameraManager->GetCameraRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}
