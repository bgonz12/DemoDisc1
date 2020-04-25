// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/SoundCue.h"

#include "ArmyMenProjectile.h"
#include "ArmyMenTargetComponent.h"
#include "DemoDisc1/DemoDisc1GameInstance.h"
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

	TargetComponent = CreateDefaultSubobject<UArmyMenTargetComponent>(TEXT("TargetComponent"));
	TargetComponent->SetupAttachment(RootComponent);

	MeshContainer = CreateDefaultSubobject<USceneComponent>(TEXT("MeshContainer"));
	MeshContainer->SetupAttachment(GetCapsuleComponent());
	GetMesh()->SetupAttachment(MeshContainer);

	// Pawn defaults
	bUseControllerRotationYaw = false;

	// Class defaults
	bIsDead = false;

	MaxHealth = 10;
	CurrentHealth = 0;

	// Set movement property defaults
	NormalWalkSpeed = 600.0f;
	SpookyWalkSpeed = 500.0f;
	
	NormalBackstepMultiplier = 0.6f;
	SpookyBackstepMultiplier = 0.4f;
	BackstepMultiplier = NormalBackstepMultiplier;

	TurnRate = 90.0f;

	NormalFireRate = 5.0f;
	SpookyFireRate = 3.0f;
	FireRate = NormalFireRate;

	// Set aiming property defaults
	AimTraceTypeQuery = ETraceTypeQuery::TraceTypeQuery4;

	NormalAimRange = 3000.0f;
	SpookyAimRange = 1100.0f;
	AimRange = NormalAimRange;

	AimBoxWidth = 500.0f;
	AimBoxHeight = 500.0f;
	AimAccuracy = 1.0f;
}

// Called when the game starts or when spawned
void AArmyMenCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	bIsDead = false;

	RespawnTransform = GetActorTransform();

	UWorld* World = GetWorld();
	if (!World) return;

	UGameInstance* GameInstance = UGameplayStatics::GetGameInstance(World);
	if (!GameInstance) return;

	UDemoDisc1GameInstance* DD1GameInstance = Cast<UDemoDisc1GameInstance>(GameInstance);
	if (!DD1GameInstance) return;

	if (!DD1GameInstance->GetHasSpookyTransitioned())
	{
		SetNormalValues();
		DD1GameInstance->OnSpookyTransition.AddDynamic(this, &AArmyMenCharacter::SetSpookyValues);
	}
	else
	{
		SetSpookyValues();
	}
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

	FVector StartPosition = GetActorLocation() + GetActorForwardVector() * 100.0f;
	FVector EndPosition = GetActorLocation() + GetActorForwardVector() * AimRange;
	FVector BoxExtents = FVector(100.0f / 2.0f, AimBoxWidth, AimBoxHeight) / 2.0f;
	FRotator Orientation = GetActorRotation();

	EDrawDebugTrace::Type DrawDebugBoxTrace = EDrawDebugTrace::None;
	if (bDrawDebugAimBox)
	{
		DrawDebugBoxTrace = EDrawDebugTrace::ForOneFrame;
	}

	TArray<AActor *> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	FHitResult OutHitBox;

	if (UKismetSystemLibrary::BoxTraceSingle(
		World,
		StartPosition,
		EndPosition,
		BoxExtents,
		Orientation,
		AimTraceTypeQuery,
		false,
		ActorsToIgnore,
		DrawDebugBoxTrace,
		OutHitBox,
		false)
	)
	{
		if(OutHitBox.GetActor() != AimTarget)
		{
			// Switch potential target
			AimTarget = nullptr;
		}

		FVector PotentialTargetLocation = OutHitBox.GetActor()->GetActorLocation();

		UArmyMenTargetComponent* AimTargetComponent = Cast<UArmyMenTargetComponent>(OutHitBox.GetActor()->GetComponentByClass(UArmyMenTargetComponent::StaticClass()));
		if (AimTargetComponent)
		{
			PotentialTargetLocation = AimTargetComponent->GetComponentLocation();
		}

		EDrawDebugTrace::Type DrawDebugLineTrace = EDrawDebugTrace::None;
		if (bDrawDebugAimLine)
		{
			DrawDebugLineTrace = EDrawDebugTrace::ForOneFrame;
		}

		FHitResult OutHitLine;

		if (UKismetSystemLibrary::LineTraceSingle(World, CharacterCamera->GetComponentLocation(),
												  PotentialTargetLocation,
												  ETraceTypeQuery::TraceTypeQuery1, false, ActorsToIgnore,
												  DrawDebugLineTrace, OutHitLine, true)
		)
		{
			if (OutHitLine.GetActor() == OutHitBox.GetActor())
			{
				AimTarget = OutHitLine.GetActor();
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


void AArmyMenCharacter::Kill()
{
	if (bIsDead) return;

	bIsDead = true;

	PlayDeathAnimation();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AArmyMenCharacter::SetNormalValues()
{
	GetCharacterMovement()->MaxWalkSpeed = NormalWalkSpeed;
	BackstepMultiplier = NormalBackstepMultiplier;
	AimRange = NormalAimRange;
	FireRate = NormalFireRate;
}

void AArmyMenCharacter::SetSpookyValues()
{
	GetCharacterMovement()->MaxWalkSpeed = SpookyWalkSpeed;
	BackstepMultiplier = SpookyBackstepMultiplier;
	AimRange = SpookyAimRange;
	FireRate = SpookyFireRate;
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

void AArmyMenCharacter::MoveForward(float Value)
{
	if (Value > 0.0f)
	{
		// get forward vector
		const FVector Direction = GetActorForwardVector();
		AddMovementInput(Direction, Value);
	}
	else if (Value < 0.0f)
	{
		// get forward vector
		const FVector Direction = GetActorForwardVector();
		AddMovementInput(Direction, Value * BackstepMultiplier);
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

	const USkeletalMeshSocket* GunNozzle = GetMesh()->GetSocketByName(FName("Muzzle"));
	if (GunNozzle)
	{
		SpawnLocation = GunNozzle->GetSocketLocation(GetMesh());
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
		FVector AimTargetLocation = AimTarget->GetActorLocation();

		UArmyMenTargetComponent* AimTargetComponent = Cast<UArmyMenTargetComponent>(AimTarget->GetComponentByClass(UArmyMenTargetComponent::StaticClass()));
		if (AimTargetComponent)
		{
			AimTargetLocation = AimTargetComponent->GetComponentLocation();
		}

		SpawnRotation = (AimTargetLocation - SpawnLocation).Rotation() + AccuracyModifier;
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

	// Animation and Effects
	PlayFireAnimation();

	if (NormalShootSound)
	{
		UGameplayStatics::PlaySoundAtLocation(World, NormalShootSound, SpawnLocation);
	}

	if (SpookyShootSound)
	{
		UGameplayStatics::PlaySoundAtLocation(World, SpookyShootSound, SpawnLocation);
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

	OnNotifyHealthChange.Broadcast();

	return DamageAmount;
}

AActor* AArmyMenCharacter::GetAimTarget()
{
	return AimTarget;
}