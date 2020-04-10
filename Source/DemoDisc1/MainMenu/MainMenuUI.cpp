// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

bool UMainMenuUI::Initialize()
{
	if (!Super::Initialize()) return false;

	Demo1Button->OnPressed.AddDynamic(this, &UMainMenuUI::Demo1ButtonPressed);
	Demo1Button->OnHovered.AddDynamic(this, &UMainMenuUI::Demo1ButtonHovered);
	Demo1Button->OnUnhovered.AddDynamic(this, &UMainMenuUI::Demo1ButtonUnhovered);

	Demo2Button->OnPressed.AddDynamic(this, &UMainMenuUI::Demo2ButtonPressed);
	Demo2Button->OnHovered.AddDynamic(this, &UMainMenuUI::Demo2ButtonHovered);
	Demo2Button->OnUnhovered.AddDynamic(this, &UMainMenuUI::Demo2ButtonUnhovered);

	return true;
}

void UMainMenuUI::Demo1ButtonPressed()
{
	UWorld* World = GetWorld();
	if (!World) return;

	UGameplayStatics::OpenLevel(World, FName("PlatformerDemoLevel"));
}

void UMainMenuUI::Demo1ButtonHovered()
{
	TitleText->SetText(Demo1Title);
}

void UMainMenuUI::Demo1ButtonUnhovered()
{
	TitleText->SetText(DefaultTitle);
}

void UMainMenuUI::Demo2ButtonPressed()
{
	UWorld* World = GetWorld();
	if (!World) return;

	UGameplayStatics::OpenLevel(World, FName("ArmyMenDemoLevel"));
}

void UMainMenuUI::Demo2ButtonHovered()
{
	TitleText->SetText(Demo2Title);
}

void UMainMenuUI::Demo2ButtonUnhovered()
{
	TitleText->SetText(DefaultTitle);
}
