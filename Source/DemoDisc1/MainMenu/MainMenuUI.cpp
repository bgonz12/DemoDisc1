// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUI.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "MediaPlayer.h"
#include "MediaSource.h"

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
	PlayPreviewTVStaticFadeIn();

	PreviewImage->SetBrushFromMaterial(Demo1PreviewMaterial);
	TitleText->SetText(Demo1Title);

	if (Demo1MediaSource && PreviewMediaPlayer)
	{
		PreviewMediaPlayer->Close();
		PreviewMediaPlayer->OpenSource(Demo1MediaSource);
	}

	PlayButtonHoverSound();
}

void UMainMenuUI::Demo1ButtonUnhovered()
{
	PlayPreviewTVStaticFadeOut();

	/*PreviewImage->SetBrushFromMaterial(DefaultPreviewMaterial);
	TitleText->SetText(DefaultTitle);

	if (PreviewMediaPlayer)
	{
		PreviewMediaPlayer->Close();
	}*/
}

void UMainMenuUI::Demo2ButtonPressed()
{
	if (!MainMenuLevelTransitioner) return;

	MainMenuLevelTransitioner->TransitionToLevel(FName("ArmyMenDemoLevel"));
}

void UMainMenuUI::Demo2ButtonHovered()
{
	PlayPreviewTVStaticFadeIn();

	PreviewImage->SetBrushFromMaterial(Demo2PreviewMaterial);
	TitleText->SetText(Demo2Title);

	if (Demo2MediaSource && PreviewMediaPlayer)
	{
		PreviewMediaPlayer->Close();
		PreviewMediaPlayer->OpenSource(Demo2MediaSource);
	}

	PlayButtonHoverSound();
}

void UMainMenuUI::Demo2ButtonUnhovered()
{
	PlayPreviewTVStaticFadeOut();

	/*PreviewImage->SetBrushFromMaterial(DefaultPreviewMaterial);
	TitleText->SetText(DefaultTitle);

	if (PreviewMediaPlayer)
	{
		PreviewMediaPlayer->Close();
	}*/
}

void UMainMenuUI::PlayButtonHoverSound()
{
	UWorld* World = GetWorld();
	if (!World) return;

	if (ButtonHoverSound)
	{
		UGameplayStatics::PlaySound2D(World, ButtonHoverSound);
	}
}