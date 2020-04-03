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

	UFUNCTION(BlueprintCallable)
	void Initialize();

	UFUNCTION(BlueprintCallable)
	void AddNormalComponent(UPrimitiveComponent* Component);

	UFUNCTION(BlueprintCallable)
	void AddSpookyComponent(UPrimitiveComponent* Component);

protected:
	UPROPERTY(BlueprintReadWrite)
	TArray<UPrimitiveComponent*> NormalComponents;

	UPROPERTY(BlueprintReadWrite)
	TArray<UPrimitiveComponent*> SpookyComponents;

	ECollisionEnabled::Type EnabledNormalCollision;

	ECollisionEnabled::Type EnabledSpookyCollision;

	bool bIsSpooky;

	UFUNCTION(BlueprintCallable)
	void DisplayNormal();

	UFUNCTION(BlueprintCallable)
	void DisplaySpooky();

public:
	FORCEINLINE bool GetIsSpooky() { return bIsSpooky; }
};
