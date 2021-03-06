// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ArmyMenPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEMODISC1_API AArmyMenPlayerController : public APlayerController
{
	GENERATED_BODY()
	

protected:
	virtual void BeginPlay() override;


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> ArmyMenUIClass;

	class UArmyMenUI* ArmyMenUI;

public:
	UFUNCTION()
	void OnPawnNotifyHealthChange();

	UFUNCTION()
	void OnPawnNotifyAmmoChange();
};
