// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DemoDisc1/ReloadableActor.h"
#include "ArmyMenCrawlerCharacter.generated.h"

UCLASS()
class DEMODISC1_API AArmyMenCrawlerCharacter : public ACharacter, public IReloadableActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AArmyMenCrawlerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Reset() override;

protected:
	/** Component References **/

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USpookyEnableActorComponent* SpookyEnableActorComponent;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CharacterCamera;

	/** Health and Life Properties **/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	int MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	int CurrentHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Health)
	bool bIsDead;

	bool bDestroyOnReset;

	FTransform RespawnTransform;

	/** Movement Properties **/

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	float TurnRate;

	/** Senses Properties **/

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* WakeSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Senses)
	float VisionDistance;

	/** Attack Properties **/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	int AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackWidth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	float AttackRate;

	float AttackTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsChasing;

	FTimerHandle ToggleCanMoveTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	float MoveToggleRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
	bool bCanMove;

	void ToggleCanMove();

	virtual void Kill();

	UFUNCTION(BlueprintImplementableEvent)
	void PlayDeathAnimation();

	UFUNCTION(BlueprintImplementableEvent)
	void ResetDeathAnimation();

public:
	void StartChase();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Value	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnRight(float Value);

	void Attack();

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	FORCEINLINE bool GetIsDead() { return bIsDead; }

	FORCEINLINE float GetAttackRange() { return AttackRange; }

	FORCEINLINE float GetVisionDistance() { return VisionDistance; }

	FORCEINLINE void SetDestroyOnReset(bool DestroyOnReset) { bDestroyOnReset = DestroyOnReset; }
};
