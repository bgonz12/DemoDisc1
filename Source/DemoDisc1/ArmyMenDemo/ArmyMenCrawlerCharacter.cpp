// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenCrawlerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/DamageType.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "DemoDisc1/SpookyEnableActorComponent.h"

// Sets default values
AArmyMenCrawlerCharacter::AArmyMenCrawlerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpookyEnableActorComponent = CreateDefaultSubobject<USpookyEnableActorComponent>(TEXT("SpookyEnableActorComponent"));

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character
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

	bDestroyOnReset = false;

	MaxHealth = 10;
	CurrentHealth = 0;

	AttackDamage = 3;
	AttackRate = 2.0f;
	AttackRange = 150.0f;
	AttackWidth = 125.0f;

	bIsChasing = false;

	MoveToggleRate = 0.5f;
	bCanMove = false;

	VisionDistance = 500.0f;

	TurnRate = 90.0f;
}

// Called when the game starts or when spawned
void AArmyMenCrawlerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;

	bIsDead = false;

	RespawnTransform = GetActorTransform();

	UWorld* World = GetWorld();
	if (!World) return;

	World->GetTimerManager().ClearTimer(ToggleCanMoveTimerHandle);
}

// Called every frame
void AArmyMenCrawlerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsDead) return;

	if (AttackTimer > 0.0f)
	{
		AttackTimer -= DeltaTime;
	}
}

void AArmyMenCrawlerCharacter::Reset()
{
	// We do not call reset on parent class because doing so Destroys the actor 
	//Super::Reset();

	if (bDestroyOnReset) Destroy();

	if (!GetIsReloadable()) return;

	CurrentHealth = MaxHealth;

	bIsDead = false;

	ResetDeathAnimation();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	SetActorTransform(RespawnTransform);
}

void AArmyMenCrawlerCharacter::ToggleCanMove()
{
	bCanMove = !bCanMove;

	if (!bCanMove)
	{
		Attack();
	}
}


void AArmyMenCrawlerCharacter::Kill()
{
	if (bIsDead) return;

	bIsDead = true;

	bIsChasing = false;

	PlayDeathAnimation();

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetSimulatePhysics(false);
}

void AArmyMenCrawlerCharacter::StartChase()
{

	bIsChasing = true;

	UWorld* World = GetWorld();
	if (!World) return;

	if (WakeSound)
	{
		UGameplayStatics::PlaySoundAtLocation(World, WakeSound, GetActorLocation());
	}

	World->GetTimerManager().ClearTimer(ToggleCanMoveTimerHandle);

	World->GetTimerManager().SetTimer(ToggleCanMoveTimerHandle, this, &AArmyMenCrawlerCharacter::ToggleCanMove, MoveToggleRate, true);
}

// Called to bind functionality to input
void AArmyMenCrawlerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(FName("MoveForward"), this, &AArmyMenCrawlerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(FName("MoveRight"), this, &AArmyMenCrawlerCharacter::TurnRight);

	PlayerInputComponent->BindAction(FName("Fire"), EInputEvent::IE_Pressed, this, &AArmyMenCrawlerCharacter::Attack);
}

void AArmyMenCrawlerCharacter::MoveForward(float Value)
{
	if (Value != 0.0f && bCanMove)
	{
		// get forward vector
		const FVector Direction = GetActorForwardVector();
		AddMovementInput(Direction, Value);
	}
}

void AArmyMenCrawlerCharacter::TurnRight(float Value)
{
	if (Value != 0.0f && bCanMove)
	{
		float YawInput = Value * TurnRate * GetWorld()->GetDeltaSeconds();

		// calculate delta for this frame from the rate information
		FRotator Rotator(0.0f, YawInput, 0.0f);
		AddActorLocalRotation(Rotator);
	}
}

void AArmyMenCrawlerCharacter::Attack()
{
	if (AttackTimer > 0.0f) return;

	UWorld* World = GetWorld();
	if (!World) return;

	FVector BoxPosition = GetActorLocation() + GetActorForwardVector() * (AttackRange / 2.0f);
	FVector BoxExtents = FVector(AttackRange, AttackWidth, AttackWidth) / 2.0f;
	FRotator Orientation = GetActorRotation();
	
	ETraceTypeQuery TraceChannel = ETraceTypeQuery::TraceTypeQuery3;

	TArray<AActor *> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	FHitResult OutHit;

	if (UKismetSystemLibrary::BoxTraceSingle(
		World,
		BoxPosition,
		BoxPosition,
		BoxExtents,
		Orientation,
		TraceChannel,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		OutHit,
		false)
	)
	{
		TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
		FDamageEvent DamageEvent(ValidDamageTypeClass);

		OutHit.GetActor()->TakeDamage(AttackDamage, DamageEvent, GetInstigatorController(), this);
	}

	AttackTimer = 1.0f / AttackRate;
}

float AArmyMenCrawlerCharacter::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
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
