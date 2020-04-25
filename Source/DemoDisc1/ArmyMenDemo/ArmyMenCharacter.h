// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DemoDisc1/ReloadableActor.h"
#include "ArmyMenCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FNotifyHealthChange, AArmyMenCharacter, OnNotifyHealthChange);

UCLASS()
class DEMODISC1_API AArmyMenCharacter : public ACharacter, public IReloadableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AArmyMenCharacter();

	FNotifyHealthChange OnNotifyHealthChange;

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

	UPROPERTY(VisibleAnywhere, blueprintReadWrite)
	class UArmyMenTargetComponent* TargetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USceneComponent* MeshContainer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	int MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	int CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	bool bIsDead;

	FTransform RespawnTransform;

	/** Movement Properties **/

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float NormalWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float SpookyWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float NormalBackstepMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float SpookyBackstepMultiplier;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement)
	float BackstepMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float TurnRate;

	float TurnInput;

	/** Shooting Properties **/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooting)
	UAnimMontage* CharacterShootMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooting)
	class USoundCue* NormalShootSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooting)
	class USoundCue* SpookyShootSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooting)
	TSubclassOf<class AArmyMenProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooting)
	TEnumAsByte<ETraceTypeQuery> AimTraceTypeQuery;

	AActor* AimTarget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooting)
	float NormalFireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooting)
	float SpookyFireRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Shooting)
	float FireRate;

	float FireTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Aiming)
	float NormalAimRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Aiming)
	float SpookyAimRange;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Aiming)
	float AimRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Aiming)
	float AimBoxWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Aiming)
	float AimBoxHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Aiming)
	float AimAccuracy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Aiming)
	bool bDrawDebugAimBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Aiming)
	bool bDrawDebugAimLine;

	virtual void Kill();

	virtual void SetNormalValues();

	UFUNCTION()
	virtual void SetSpookyValues();

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

	UFUNCTION(BlueprintCallable)
	AActor* GetAimTarget();

	FORCEINLINE int GetMaxHealth() { return MaxHealth; }

	FORCEINLINE int GetCurrentHealth() { return CurrentHealth; }

	FORCEINLINE bool GetIsDead() { return bIsDead; }

	FORCEINLINE void SetRespawnTransform(FTransform NewRespawnTransform) { RespawnTransform = NewRespawnTransform; }
};
