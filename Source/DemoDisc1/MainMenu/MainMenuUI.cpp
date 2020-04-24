// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"

#include "DemoDisc1/LevelTransitioner.h"

bool UMainMenuUI::Initialize()
{
	if (!Super::Initialize()) return false;

	PreviewImage->SetBrushFromMaterial(DefaultPreviewMaterial);

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
	if (!MainMenuLevelTransitioner) return;

	MainMenuLevelTransitioner->TransitionToLevel(FName("PlatformerDemoLevel"));
}

void UMainMenuUI::Demo1ButtonHovered()
{
	PreviewImage->SetBrushFromMaterial(Demo1PreviewMaterial);
	TitleText->SetText(Demo1Title);
}

void UMainMenuUI::Demo1ButtonUnhovered()
{
	PreviewImage->SetBrushFromMaterial(DefaultPreviewMaterial);
	TitleText->SetText(DefaultTitle);
}

void UMainMenuUI::Demo2ButtonPressed()
{
	if (!MainMenuLevelTransitioner) return;

	MainMenuLevelTransitioner->TransitionToLevel(FName("ArmyMenDemoLevel"));
}

void UMainMenuUI::Demo2ButtonHovered()
{
	PreviewImage->SetBrushFromMaterial(Demo2PreviewMaterial);
	TitleText->SetText(Demo2Title);
}

void UMainMenuUI::Demo2ButtonUnhovered()
{
	PreviewImage->SetBrushFromMaterial(DefaultPreviewMaterial);
	TitleText->SetText(DefaultTitle);
}
