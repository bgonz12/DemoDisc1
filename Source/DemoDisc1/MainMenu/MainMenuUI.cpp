// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUI.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UMainMenuUI::Initialize()
{
	if (!Super::Initialize()) return false;

	Demo1Button->OnPressed.AddDynamic(this, &UMainMenuUI::Demo1ButtonPressed);
	Demo2Button->OnPressed.AddDynamic(this, &UMainMenuUI::Demo2ButtonPressed);

	return true;
}

void UMainMenuUI::Demo1ButtonPressed()
{
	UWorld* World = GetWorld();
	if (!World) return;

	UGameplayStatics::OpenLevel(World, FName("PlatformerDemoLevel"));
}

void UMainMenuUI::Demo2ButtonPressed()
{
	UWorld* World = GetWorld();
	if (!World) return;

	UGameplayStatics::OpenLevel(World, FName("ArmyMenDemoLevel"));
}
