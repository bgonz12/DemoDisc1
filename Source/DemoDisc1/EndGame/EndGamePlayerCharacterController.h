// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EndGamePlayerCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class DEMODISC1_API AEndGamePlayerCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	AEndGamePlayerCharacterController();

protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> EndGameUIClass;

	class UEndGameUI* EndGameUI;

public:
	class UEndGameUI* GetEndGameUI();
};
