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

	bIsMainMenuOpen = true;

	PreviewImage->SetBrushFromMaterial(DefaultPreviewMaterial);

	Button1->OnPressed.AddDynamic(this, &UMainMenuUI::Demo1ButtonPressed);
	Button1->OnHovered.AddDynamic(this, &UMainMenuUI::Demo1ButtonHovered);
	Button1->OnUnhovered.AddDynamic(this, &UMainMenuUI::Demo1ButtonUnhovered);

	Button2->OnPressed.AddDynamic(this, &UMainMenuUI::Demo2ButtonPressed);
	Button2->OnHovered.AddDynamic(this, &UMainMenuUI::Demo2ButtonHovered);
	Button2->OnUnhovered.AddDynamic(this, &UMainMenuUI::Demo2ButtonUnhovered);

	CreditsButton->OnPressed.AddDynamic(this, &UMainMenuUI::CreditsButtonPressed);
	CreditsButton->OnHovered.AddDynamic(this, &UMainMenuUI::CreditsButtonHovered);
	CreditsButton->OnUnhovered.AddDynamic(this, &UMainMenuUI::CreditsButtonUnhovered);

	CreditsBackButton->OnPressed.AddDynamic(this, &UMainMenuUI::CreditsBackButtonPressed);

	return true;
}

void UMainMenuUI::Demo1ButtonPressed()
{
	if (!MainMenuLevelTransitioner) return;

	MainMenuLevelTransitioner->TransitionToLevel(FName("PlatformerDemoLevel"));

	PlayButtonPressSound();
}

void UMainMenuUI::Demo1ButtonHovered()
{
	PlayPreviewTVStaticFadeIn();

	PreviewImage->SetBrushFromMaterial(Button1PreviewMaterial);
	TitleImage->SetBrushFromMaterial(Button1TitleMaterial);

	if (Button1MediaSource && PreviewMediaPlayer)
	{
		PreviewMediaPlayer->Close();
		PreviewMediaPlayer->OpenSource(Button1MediaSource);
	}

	PlayButtonHoverSound();
}

void UMainMenuUI::Demo1ButtonUnhovered()
{
	PlayPreviewTVStaticFadeOut();

	TitleImage->SetBrushFromMaterial(DefaultTitleMaterial);
}

void UMainMenuUI::Demo2ButtonPressed()
{
	if (!MainMenuLevelTransitioner) return;

	MainMenuLevelTransitioner->TransitionToLevel(FName("ArmyMenDemoLevel"));

	PlayButtonPressSound();
}

void UMainMenuUI::Demo2ButtonHovered()
{
	PlayPreviewTVStaticFadeIn();

	PreviewImage->SetBrushFromMaterial(Button2PreviewMaterial);
	TitleImage->SetBrushFromMaterial(Button2TitleMaterial);

	if (Button2MediaSource && PreviewMediaPlayer)
	{
		PreviewMediaPlayer->Close();
		PreviewMediaPlayer->OpenSource(Button2MediaSource);
	}

	PlayButtonHoverSound();
}

void UMainMenuUI::Demo2ButtonUnhovered()
{
	PlayPreviewTVStaticFadeOut();

	TitleImage->SetBrushFromMaterial(DefaultTitleMaterial);
}

void UMainMenuUI::CreditsButtonPressed()
{
	if (!bIsMainMenuOpen) return;

	bIsMainMenuOpen = false;

	PlayTransitionToCredits();

	PlayButtonPressSound();
}

void UMainMenuUI::CreditsButtonHovered()
{
	PlayPreviewTVStaticFadeIn();

	PreviewImage->SetBrushFromMaterial(CreditsPreviewMaterial);
	TitleImage->SetBrushFromMaterial(CreditsTitleMaterial);

	PlayButtonHoverSound();
}

void UMainMenuUI::CreditsButtonUnhovered()
{
	PlayPreviewTVStaticFadeOut();

	TitleImage->SetBrushFromMaterial(DefaultTitleMaterial);
}

void UMainMenuUI::CreditsBackButtonPressed()
{
	if (bIsMainMenuOpen) return;

	bIsMainMenuOpen = true;

	PlayTransitionToMainMenu();

	PlayButtonPressSound();
}

void UMainMenuUI::PlayButtonPressSound()
{
	UWorld* World = GetWorld();
	if (!World) return;

	if (ButtonPressSound)
	{
		UGameplayStatics::PlaySound2D(World, ButtonPressSound);
	}
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