// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ArmyMenCharacter.generated.h"

UCLASS()
class DEMODISC1_API AArmyMenCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AArmyMenCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CharacterCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooting)
	TSubclassOf<class AArmyMenProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooting)
	TEnumAsByte<ETraceTypeQuery> AimTraceTypeQuery;

	AActor* AimTarget;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Camera)
	float TurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooting)
	float AimRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooting)
	float AimSphereRadius;

public:
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Value	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnRight(float Value);

	void Fire();

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
