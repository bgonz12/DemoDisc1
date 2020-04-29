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
	class UTextBlock* TitleText;

	UPROPERTY(meta = (BindWidget))
	class UButton* Demo1Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* Demo2Button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoundBase* ButtonHoverSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterialInterface* DefaultPreviewMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterialInterface* Demo1PreviewMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterialInterface* Demo2PreviewMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMaterialInterface* Demo3PreviewMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMediaPlayer* PreviewMediaPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMediaSource* Demo1MediaSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UMediaSource* Demo2MediaSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DefaultTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Demo1Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Demo2Title;

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
