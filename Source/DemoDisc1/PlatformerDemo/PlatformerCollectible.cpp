// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerCollectible.h"
#include "Components/MaterialBillboardComponent.h"
#include "Components/SphereComponent.h"

#include "PlatformerCharacter.h"
#include "PlatformerCharacterController.h"
#include "PlatformerUI.h"

// Sets default values
APlatformerCollectible::APlatformerCollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);

	MaterialBillboardComponent = CreateDefaultSubobject<UMaterialBillboardComponent>(TEXT("MaterialBillboardComponent"));
	MaterialBillboardComponent->SetupAttachment(SphereComponent);
}

// Called when the game starts or when spawned
void APlatformerCollectible::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &APlatformerCollectible::BeginOverlap);
}

// Called every frame
void APlatformerCollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformerCollectible::BeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	APlatformerCharacter* Character = Cast<APlatformerCharacter>(OtherActor);
	if (!Character) return;

	AController* Controller = Character->GetController();
	if (!Controller) return;

	APlatformerCharacterController* CharacterController = Cast<APlatformerCharacterController>(Controller);
	if (!CharacterController) return;
	
	UPlatformerUI* PlatformerUI = CharacterController->GetPlatformerUI();
	if (!PlatformerUI) return;
	
	PlatformerUI->PlayShowCollectables();
	Destroy();
}