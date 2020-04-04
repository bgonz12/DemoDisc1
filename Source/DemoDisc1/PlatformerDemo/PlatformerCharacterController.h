// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlatformerCharacterController.generated.h"

/**
 * 
 */
UCLASS()
class DEMODISC1_API APlatformerCharacterController : public APlayerController
{
	GENERATED_BODY()
	
public:
	APlatformerCharacterController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> PlatformerUIClass;

	class UPlatformerUI* PlatformerUI;

public:
	class UPlatformerUI* GetPlatformerUI();

	virtual void Reset() override;
};
