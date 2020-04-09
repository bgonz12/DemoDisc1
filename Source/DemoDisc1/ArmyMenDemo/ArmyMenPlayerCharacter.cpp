// Fill out your copyright notice in the Description page of Project Settings.


#include "ArmyMenPlayerCharacter.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include "ArmyMenPlayerController.h"
#include "ArmyMenGameModeBase.h"

void AArmyMenPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	AController* MyController = GetController();
	if (!MyController) return;

	PlayerController = Cast<AArmyMenPlayerController>(MyController);
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