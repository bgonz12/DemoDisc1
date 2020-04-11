// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DemoDisc1/ReloadableActor.h"
#include "ArmyMenCharacter.generated.h"

UCLASS()
class DEMODISC1_API AArmyMenCharacter : public ACharacter, public IReloadableActor
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

	virtual void Reset() override;

protected:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDutchAngleCameraComponent* CharacterCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USceneComponent* GunMeshContainer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	int MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	int CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	bool bIsDead;

	FTransform RespawnTransform;

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float TurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooting)
	UAnimMontage* CharacterShootMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooting)
	UAnimMontage* GunShootMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooting)
	TSubclassOf<class AArmyMenProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooting)
	TEnumAsByte<ETraceTypeQuery> AimTraceTypeQuery;

	AActor* AimTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooting)
	float FireRate;

	float FireTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Aiming)
	float AimRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Aiming)
	float AimSphereRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Aiming)
	float AimAccuracy;

	virtual void Kill();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayFireAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayDeathAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void ResetDeathAnimation();

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Value	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnRight(float Value);

	void Fire();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	FORCEINLINE AActor* GetAimTarget() { return AimTarget; }

	FORCEINLINE bool GetIsDead() { return bIsDead; }

	FORCEINLINE void SetRespawnTransform(FTransform NewRespawnTransform) { RespawnTransform = NewRespawnTransform; }
};
