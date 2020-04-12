// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Engine/World.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#include "ArmyMenProjectile.h"
#include "DemoDisc1/DutchAngleCameraComponent.h"

// Sets default values
AArmyMenCharacter::AArmyMenCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 5.0f; // The camera follows at this distance behind the character
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bAbsoluteRotation = false;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = true;

	// Create a follow camera
	CharacterCamera = CreateDefaultSubobject<UDutchAngleCameraComponent>(TEXT("CharacterCamera"));
	CharacterCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	CharacterCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	GunMeshContainer = CreateDefaultSubobject<USceneComponent>(TEXT("GunMeshContainer"));
	GunMeshContainer->SetupAttachment(GetMesh(), FName("RightHand"));

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	GunMesh->SetupAttachment(GunMeshContainer);

	// Pawn defaults
	bUseControllerRotationYaw = false;

	// Class defaults
	bIsDead = false;

	MaxHealth = 10;
	CurrentHealth = 0;

	TurnRate = 90.0f;

	FireRate = 1.0f;

	AimTraceTypeQuery = ETraceTypeQuery::TraceTypeQuery4;
	AimRange = 3000.0f;
	AimSphereRadius = 300.0f;
	AimAccuracy = 1.0f;
}

// Called when the game starts or when spawned
void AArmyMenCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	bIsDead = false;

	RespawnTransform = GetActorTransform();
}

// Called every frame
void AArmyMenCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsDead) return;

	if (FireTimer > 0.0f)
	{
		FireTimer -= DeltaTime;
	}

	UWorld* World = GetWorld();
	if (!World) return;

	FVector TraceStart = GetActorLocation() + GetActorForwardVector() * (AimSphereRadius + 100.0f);
	FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * AimRange;

	TArray<AActor *> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	EDrawDebugTrace::Type DrawDebugSphereTrace = EDrawDebugTrace::None;
	if (bDrawDebugAimSphere)
	{
		 DrawDebugSphereTrace = EDrawDebugTrace::ForOneFrame;
	}

	FHitResult OutHitSphere;

	if (UKismetSystemLibrary::SphereTraceSingle(World, TraceStart, TraceEnd, AimSphereRadius, 
												AimTraceTypeQuery, false, ActorsToIgnore,
												DrawDebugSphereTrace, OutHitSphere, true)
	)
	{
		if(OutHitSphere.GetActor() != AimTarget)
		{
			// Switch potential target
			AimTarget = nullptr;
		}

		EDrawDebugTrace::Type DrawDebugLineTrace = EDrawDebugTrace::None;
		if (bDrawDebugAimLine)
		{
			DrawDebugLineTrace = EDrawDebugTrace::ForOneFrame;
		}

		FHitResult OutHitLine;

		if (UKismetSystemLibrary::LineTraceSingle(World, CharacterCamera->GetComponentLocation(),
												  OutHitSphere.GetActor()->GetActorLocation(),
												  ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore,
												  DrawDebugLineTrace, OutHitLine, true)
		)
		{
			if (OutHitLine.GetActor() == OutHitSphere.GetActor())
			{
				AimTarget = OutHitLine.GetActor();
			}
		}
		else
		{
			AimTarget = nullptr;
		}
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

	if (!GetIsReloadable()) return;

	CurrentHealth = MaxHealth;
	OnNotifyHealthChange.Broadcast();

	bIsDead = false;

	ResetDeathAnimation();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	SetActorTransform(RespawnTransform);
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
	TurnInput = Value;

	if (Value != 0.0f)
	{
		float TurnAmount = TurnInput * TurnRate * GetWorld()->GetDeltaSeconds();

		// calculate delta for this frame from the rate information
		FRotator Rotator(0.0f, TurnAmount, 0.0f);
		AddActorLocalRotation(Rotator);
	}
}

void AArmyMenCharacter::Fire()
{
	if (FireTimer > 0.0f) return;

	if (ProjectileClass == nullptr) return;

	UWorld* World = GetWorld();
	if (!World) return;

	/** Spawn Bullet **/

	FVector SpawnLocation;

	const USkeletalMeshSocket* GunNozzle = GunMesh->GetSocketByName(FName("Nozzle"));
	if (GunNozzle)
	{
		SpawnLocation = GunNozzle->GetSocketLocation(GunMesh);
	}
	else
	{
		SpawnLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
	}

	float AccuracyX = FMath::FRandRange(-1.0f, 1.0f) * 90.0f * (1.0f - AimAccuracy);
	float AccuracyY = FMath::FRandRange(-1.0f, 1.0f) * 90.0f * (1.0f - AimAccuracy);
	FRotator AccuracyModifier(AccuracyX, AccuracyY, 0.0f);

	FRotator SpawnRotation;
	if (AimTarget)
	{
		SpawnRotation = (AimTarget->GetActorLocation() - SpawnLocation).Rotation() + AccuracyModifier;
	}
	else
	{
		SpawnRotation = GetActorRotation() + AccuracyModifier;
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

	PlayFireAnimation();

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

	OnNotifyHealthChange.Broadcast();

	return DamageAmount;
}
