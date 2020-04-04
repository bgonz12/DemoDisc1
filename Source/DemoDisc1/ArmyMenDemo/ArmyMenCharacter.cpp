// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"

#include "ArmyMenProjectile.h"

// Sets default values
AArmyMenCharacter::AArmyMenCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f; // The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller

	// Create a follow camera
	CharacterCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CharacterCamera"));
	CharacterCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	CharacterCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	BaseTurnRate = 40.0f;
}

// Called when the game starts or when spawned
void AArmyMenCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArmyMenCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AArmyMenCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AArmyMenCharacter::TurnAtRate);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AArmyMenCharacter::MoveForward);

	PlayerInputComponent->BindAction(FName("Jump"), EInputEvent::IE_Pressed, this, &AArmyMenCharacter::Fire);
	PlayerInputComponent->BindAction(FName("Fire"), EInputEvent::IE_Pressed, this, &AArmyMenCharacter::Fire);
}

void AArmyMenCharacter::TurnAtRate(float Rate)
{

	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AArmyMenCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// get forward vector
		const FVector Direction = GetActorForwardVector();
		AddMovementInput(Direction, Value);
	}
}

void AArmyMenCharacter::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("TEST 1"));

	if (ProjectileClass == nullptr) return;

	UE_LOG(LogTemp, Warning, TEXT("TEST 2"));

	UWorld* World = GetWorld();
	if (!World) return;

	UE_LOG(LogTemp, Warning, TEXT("TEST 3"));

	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
	FRotator SpawnRotation = GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.Owner = this;

	World->SpawnActor<AArmyMenProjectile>(ProjectileClass->StaticClass(), SpawnLocation, SpawnRotation, SpawnParams);

	UE_LOG(LogTemp, Warning, TEXT("TEST 4"));
}
