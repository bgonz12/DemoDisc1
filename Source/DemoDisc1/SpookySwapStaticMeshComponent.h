// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "SpookySwapInterface.h"
#include "SpookySwapStaticMeshComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DEMODISC1_API USpookySwapStaticMeshComponent : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsSpooky;

	ECollisionEnabled::Type EnabledCollision;

	UFUNCTION()
	void SwapToNormal();

	UFUNCTION()
	void SwapToSpooky();

public:
	FORCEINLINE bool GetIsSpooky() { return bIsSpooky; }
};
