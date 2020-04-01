// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerUI.h"
#include "Components/TextBlock.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

#include "PlatformerGameModeBase.h"

bool UPlatformerUI::Initialize()
{
	if(!Super::Initialize()) return false;

	PlayCurtainFadeIn();

	PlayShowCollectables();

	UWorld* World = GetWorld();
	if (!World) return false;

	AGameModeBase* GameMode = UGameplayStatics::GetGameMode(World);
	if (!GameMode) return false;

	APlatformerGameModeBase* PlatformerGameMode = Cast<APlatformerGameModeBase>(GameMode);
	if (!PlatformerGameMode) return false;

	PlatformerGameMode->OnCollectibleCountUpdated.AddDynamic(this, &UPlatformerUI::SetCollectibleCounter);

	return true;
}

int UPlatformerUI::GetCollectibleCounter()
{
	return CollectibleCounter;
}

void UPlatformerUI::SetCollectibleCounter(int Value)
{
	CollectibleCounter = Value;

	CollectibleText->SetText(FText::FromString(FString::FromInt(Value)));

	PlayShowCollectables();
}
