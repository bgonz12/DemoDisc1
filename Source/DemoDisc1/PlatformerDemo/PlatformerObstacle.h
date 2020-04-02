// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformerObstacle.generated.h"

UCLASS()
class DEMODISC1_API APlatformerObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformerObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	virtual void Reset() override;

protected:
	UPROPERTY()
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USceneComponent* MeshContainer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* NormalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* SpookyMesh;

	bool bHasFallenOver;

	UFUNCTION(BlueprintImplementableEvent)
	void PlayFallOverAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void ResetFallOverAnimation();

	UFUNCTION()
	void BeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
};
