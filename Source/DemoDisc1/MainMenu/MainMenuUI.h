// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUI.generated.h"

/**
 * 
 */
UCLASS()
class DEMODISC1_API UMainMenuUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual bool Initialize() override;

protected:
	class ILevelTransitioner* MainMenuLevelTransitioner;

	UPROPERTY(meta = (BindWidget))
	class UImage* PreviewImage;

	UPROPERTY(meta = (BindWidget))
	class UImage* TitleImage;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button1;

	UPROPERTY(meta = (BindWidget))
	class UButton* Button2;

	UPROPERTY(meta = (BindWidget))
	class UButton* CreditsButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* CreditsBackButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Buttons)
	class UMediaPlayer* PreviewMediaPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Buttons)
	class USoundBase* ButtonPressSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Buttons)
	class USoundBase* ButtonHoverSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	class UMaterialInterface* DefaultPreviewMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Default)
	class UMaterialInterface* DefaultTitleMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Demo1)
	class UMaterialInterface* Button1PreviewMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Demo1)
	class UMaterialInterface* Button1TitleMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Demo1)
	class UMediaSource* Button1MediaSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Demo2)
	class UMaterialInterface* Button2PreviewMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Demo2)
	class UMediaSource* Button2MediaSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Demo2)
	class UMaterialInterface* Button2TitleMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Credits)
	class UMaterialInterface* CreditsPreviewMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Credits)
	class UMaterialInterface* CreditsTitleMaterial;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsMainMenuOpen;

	void PlayButtonPressSound();

	void PlayButtonHoverSound();

	UFUNCTION()
	void Demo1ButtonPressed();

	UFUNCTION()
	void Demo1ButtonHovered();

	UFUNCTION()
	void Demo1ButtonUnhovered();

	UFUNCTION()
	void Demo2ButtonPressed();
	
	UFUNCTION()
	void Demo2ButtonHovered();

	UFUNCTION()
	void Demo2ButtonUnhovered();

	UFUNCTION()
	void CreditsButtonPressed();

	UFUNCTION()
	void CreditsButtonHovered();

	UFUNCTION()
	void CreditsButtonUnhovered();

	UFUNCTION(BlueprintCallable)
	void CreditsBackButtonPressed();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayTransitionToCredits();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayTransitionToMainMenu();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayPreviewTVStaticFadeOut();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayPreviewTVStaticFadeIn();

public:
	UFUNCTION(BlueprintImplementableEvent)
	void PlayCurtainFadeIn(float Delay);

	UFUNCTION(BlueprintImplementableEvent)
	void PlayCurtainFadeOut(float Delay);

	FORCEINLINE void SetMainMenuLevelTransitioner(class ILevelTransitioner* NewMainMenuLevelTransitioner) { MainMenuLevelTransitioner = NewMainMenuLevelTransitioner; }

};
