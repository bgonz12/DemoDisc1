// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpookySwapActor.generated.h"

UCLASS()
class DEMODISC1_API ASpookySwapActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpookySwapActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> NormalActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> SpookyActors;

	FTimerHandle InitializeTickTimerHandle;

	bool bIsSpooky;

	UFUNCTION(BlueprintCallable)
	void EnableNormal();

	UFUNCTION(BlueprintCallable)
	void EnableSpooky();
};
