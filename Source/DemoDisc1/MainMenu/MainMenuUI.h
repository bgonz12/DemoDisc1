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
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TitleText;

	UPROPERTY(meta = (BindWidget))
	class UButton* Demo1Button;

	UPROPERTY(meta = (BindWidget))
	class UButton* Demo2Button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DefaultTitle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Demo1Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Demo2Title;

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

};
