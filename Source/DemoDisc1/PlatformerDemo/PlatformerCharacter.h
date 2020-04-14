// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlatformerCharacter.generated.h"

UENUM(BlueprintType)
enum class DeathAnimationType : uint8 {
	DROWN UMETA(DisplayName = "Drown"),
	FALL UMETA(DisaplayName = "Fall"),
	SPOOKY_LADY UMETA(DisaplayName = "Spooky Lady"),
	SQUISH UMETA(DisaplayName = "Squish")
};

UCLASS()
class DEMODISC1_API APlatformerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlatformerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Reset() override;

protected:

	/** Component References **/

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CharacterCamera;

	UPROPERTY()
	class APlatformerCharacterController* PlayerController;

	/** Class Properties **/

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	UPROPERTY(EditAnywhere, Category = Jump)
	float JumpGravity;

	UPROPERTY(EditAnywhere, Category = Jump)
	float FallGravity;

	UPROPERTY(BlueprintReadWrite)
	bool bIsDead;

	FTransform RespawnTransform;

	/** Class Member Functions **/

	UFUNCTION(BlueprintImplementableEvent)
	void PlayPlayerDeathAnimation(DeathAnimationType AnimType);

	UFUNCTION(BlueprintImplementableEvent)
	void ResetPlayerDeathAnimation();

	virtual void Jump() override;

	virtual void StopJumping() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void Turn(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUp(float Rate);

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	void KillPlayer(DeathAnimationType AnimType);

	/** GETTERS **/

	/** Returns CameraBoom subobject */
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject */
	FORCEINLINE class UCameraComponent* GetCharacterCamera() const { return CharacterCamera; }

	FORCEINLINE bool GetIsDead() const { return bIsDead; }

	/** SETTERS **/

	FORCEINLINE void SetRespawnTransform(FTransform NewRespawnTransform) { RespawnTransform = NewRespawnTransform;  }
};
