// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpookyEnableActorComponent.generated.h"

UENUM()
enum ESpookyEnableBehavior { ALWAYS_ENABLED, ENABLED_ON_NORMAL, ENABLED_ON_SPOOKY };

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMODISC1_API USpookyEnableActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpookyEnableActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ESpookyEnableBehavior> EnableBehavior;

	FTimerHandle InitializeEnableTimerHandle;

	bool bIsEnabled;

	UFUNCTION()
	void Enable();

	UFUNCTION()
	void Disable();
};
