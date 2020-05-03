// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DemoDisc1/ReloadableActor.h"
#include "ArmyMenCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FNotifyHealthChange, AArmyMenCharacter, OnNotifyHealthChange);

DECLARE_DYNAMIC_MULTICAST_SPARSE_DELEGATE(FNotifyAmmoChange, AArmyMenCharacter, OnNotifyAmmoChange);


UCLASS()
class DEMODISC1_API AArmyMenCharacter : public ACharacter, public IReloadableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AArmyMenCharacter();

	FNotifyHealthChange OnNotifyHealthChange;

	FNotifyAmmoChange OnNotifyAmmoChange;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Reset() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USpookyEnableActorComponent* SpookyEnableActorComponent;

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

	/** Health Properties **/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	class USoundBase* NormalDeathSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	class USoundBase* SpookyDeathSound;

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
	class USoundCue* EmptyClickSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooting)
	class UParticleSystem* NormalMuzzleFlashParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Shooting)
	class UParticleSystem* SpookyMuzzleFlashParticle;

	class UParticleSystem* MuzzleFlashParticle;

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

	/** Aiming properties **/

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
	float NormalAimAccuracy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Aiming)
	float SpookyAimAccuracy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Aiming)
	float AimAccuracy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Aiming)
	bool bDrawDebugAimBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Aiming)
	bool bDrawDebugAimLine;

	/** Ammo properties **/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ammo)
	int NormalStartAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ammo)
	int SpookyStartAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ammo)
	int StartAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ammo)
	int MaxInventoryAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ammo)
	int InventoryAmmo;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ammo)
	int MaxLoadedAmmo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Ammo)
	int LoadedAmmo;

	bool bIsReloading;

	virtual void Kill();

	virtual void SetNormalValues();

	UFUNCTION()
	virtual void SetSpookyValues();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayFireAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayReloadAnimation();

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

	void TriggerFire();

	bool Fire();

	void TriggerReload();

	bool ReloadStart();

	UFUNCTION(BlueprintCallable)
	bool ReloadEnd();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintCallable)
	AActor* GetAimTarget();

	FORCEINLINE int GetMaxHealth() { return MaxHealth; }

	FORCEINLINE int GetCurrentHealth() { return CurrentHealth; }

	FORCEINLINE int GetInventoryAmmo() { return InventoryAmmo; }

	FORCEINLINE int GetLoadedAmmo() { return LoadedAmmo; }

	FORCEINLINE bool GetIsDead() { return bIsDead; }

	FORCEINLINE void SetRespawnTransform(FTransform NewRespawnTransform) { RespawnTransform = NewRespawnTransform; }
};
