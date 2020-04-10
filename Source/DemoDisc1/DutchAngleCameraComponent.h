// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "DutchAngleCameraComponent.generated.h"

/**
 * 
 */
UCLASS(HideCategories = (Mobility, Rendering, LOD), Blueprintable, ClassGroup = Camera, meta = (BlueprintSpawnableComponent))
class DEMODISC1_API UDutchAngleCameraComponent : public UCameraComponent
{
	GENERATED_BODY()
	
public:
	UDutchAngleCameraComponent(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float bIsSpooky;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DutchMaxAngle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DutchRotateSpeed;

	UFUNCTION(BlueprintCallable)
	void SetNormal();

	UFUNCTION(BlueprintCallable)
	void SetSpooky();
};
