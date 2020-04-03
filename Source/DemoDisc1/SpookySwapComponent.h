// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpookySwapComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMODISC1_API USpookySwapComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpookySwapComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(BlueprintReadWrite)
	TArray<UPrimitiveComponent*> NormalComponents;

	UPROPERTY(BlueprintReadWrite)
	TArray<UPrimitiveComponent*> SpookyComponents;

	ECollisionEnabled::Type EnabledNormalCollision;

	ECollisionEnabled::Type EnabledSpookyCollision;

	UFUNCTION(BlueprintCallable)
	void Initialize();

	UFUNCTION(BlueprintCallable)
	void AddNormalComponent(UPrimitiveComponent* Component);

	UFUNCTION(BlueprintCallable)
	void AddSpookyComponent(UPrimitiveComponent* Component);

	UFUNCTION(BlueprintCallable)
	void DisplayNormal();

	UFUNCTION(BlueprintCallable)
	void DisplaySpooky();
};
