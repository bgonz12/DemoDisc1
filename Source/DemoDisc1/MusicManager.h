// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MusicManager.generated.h"


UCLASS()
class DEMODISC1_API AMusicManager : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	AMusicManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MusicTransitionLerpSpeed;

	float SpookyValue;

	float TargetSpookyValue;

	UFUNCTION(BlueprintCallable)
	void TransitionToNormal();

	UFUNCTION(BlueprintCallable)
	void TransitionToSpooky();
};
