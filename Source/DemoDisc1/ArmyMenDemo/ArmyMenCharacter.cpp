// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#include "ArmyMenProjectile.h"

// Sets default values
AArmyMenCharacter::AArmyMenCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f; // The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bAbsoluteRotation = false;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = true;

	// Create a follow camera
	CharacterCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CharacterCamera"));
	CharacterCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	CharacterCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Pawn defaults
	bUseControllerRotationYaw = false;

	// Class defaults
	bIsDead = false;

	StartingHealth = 10;
	MaxHealth = 10;
	CurrentHealth = 10;

	TurnRate = 90.0f;

	FireRate = 1.0f;

	AimTraceTypeQuery = ETraceTypeQuery::TraceTypeQuery4;
	AimRange = 2000.0f;
	AimSphereRadius = 100.0f;
}

// Called when the game starts or when spawned
void AArmyMenCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	bIsDead = false;

	CurrentHealth = StartingHealth;
}

// Called every frame
void AArmyMenCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FireTimer > 0.0f)
	{
		FireTimer -= DeltaTime;
	}

	UWorld* World = GetWorld();
	if (!World) return;

	FVector TraceStart = GetActorLocation() + GetActorForwardVector() * AimSphereRadius * 2.0f;
	FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * AimRange;

	const TArray<AActor *> ActorsToIgnore;

	FHitResult OutHit;

	if (UKismetSystemLibrary::SphereTraceSingle(
		World,
		TraceStart,
		TraceEnd,
		AimSphereRadius,
		AimTraceTypeQuery, // 'Enemy' trace channel
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		OutHit,
		true)
	)
	{
		AimTarget = OutHit.Actor.Get();
	}
	else
	{
		AimTarget = nullptr;
	}
}

void AArmyMenCharacter::Reset()
{
	// We do not call reset on parent class because doing so Destroys the actor 
	//Super::Reset();

	bIsDead = false;

	ResetDeathAnimation();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetCapsuleComponent()->SetSimulatePhysics(true);
}

// Called to bind functionality to input
void AArmyMenCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AArmyMenCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AArmyMenCharacter::TurnRight);

	PlayerInputComponent->BindAction(FName("Jump"), EInputEvent::IE_Pressed, this, &AArmyMenCharacter::Fire);
	PlayerInputComponent->BindAction(FName("Fire"), EInputEvent::IE_Pressed, this, &AArmyMenCharacter::Fire);
}

void AArmyMenCharacter::Kill()
{
	if (bIsDead) return;

	bIsDead = true;

	PlayDeathAnimation();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetSimulatePhysics(false);
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

void AArmyMenCharacter::TurnRight(float Value)
{
	if (Value != 0.0f)
	{
		float YawInput = Value * TurnRate * GetWorld()->GetDeltaSeconds();

		// calculate delta for this frame from the rate information
		FRotator Rotator(0.0f, YawInput, 0.0f);
		AddActorLocalRotation(Rotator);
	}
}

void AArmyMenCharacter::Fire()
{
	if (FireTimer > 0.0f) return;

	if (ProjectileClass == nullptr) return;

	UWorld* World = GetWorld();
	if (!World) return;

	FVector SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
	FRotator SpawnRotation;

	if (AimTarget)
	{
		SpawnRotation = (AimTarget->GetActorLocation() - SpawnLocation).Rotation();
	}
	else
	{
		SpawnRotation = GetActorRotation();
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = this;
	SpawnParams.Owner = this;

	AArmyMenProjectile* Projectile = World->SpawnActor<AArmyMenProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, SpawnParams);
	
	UCapsuleComponent* MyCapsuleComponent = GetCapsuleComponent();
	if (Projectile && MyCapsuleComponent)
	{
		MyCapsuleComponent->IgnoreActorWhenMoving(Projectile, true);
	}

	FireTimer = 1.0f / FireRate;
}


float AArmyMenCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
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
