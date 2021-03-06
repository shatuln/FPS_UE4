// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectiles.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "WeaponGun.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class FIRSTFPS_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Handles input for moving forward and backward.
	UFUNCTION()
		void MoveForward(float Value);

	// Handles input for moving right and left.
	UFUNCTION()
		void MoveRight(float Value);

	// Function that handles firing projectiles.
	UFUNCTION()
		void Fire();

	UFUNCTION()
		void Reload();

	UFUNCTION()
		void StartBoosting();

	UFUNCTION()
		void StopBoosting();

	UFUNCTION()
		void StartCrouch();

	UFUNCTION()
		void StopCrouch();

	UFUNCTION()
		void StopFire();

	UFUNCTION()
		void OnFireTimer();

	UFUNCTION()
		void OnReloadTimer();

	bool bIsFiring = false;
	bool bIsFireWaiting = false;

	bool bIsBoosting = false;

	/*
	// Sets jump flag when key is pressed.
	UFUNCTION()
		void StartJump();

	// Clears jump flag when key is released.
	UFUNCTION()
		void StopJump();

	*/
	// FPS camera.
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* FPSCameraComponent;

	// First-person mesh (arms), visible only to the owning player.
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* FPSMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* TPMesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleDefaultsOnly)
		USceneComponent* WeaponFrontLocation;

	UPROPERTY(VisibleDefaultsOnly)
		UAnimInstance* FPSAnimInstance;

	//UPROPERTY(VisibleAnywhere)
	//	TSubclassOf<class AWeaponGun> WeaponGunClass;

	UPROPERTY(VisibleAnywhere)
		AWeaponGun* WeaponGun;

	unsigned int WeaponAmmo;
	const unsigned int WeaponAmmoMax = 30;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category = "Projectiles")
		TSubclassOf<class AProjectiles> ProjectileClass;

	//Timers for fire
	FTimerHandle FireTimerHandle;
	FTimerHandle ReloadTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		class UAnimMontage* FireAnimation;

	UPROPERTY(VisibleAnywhere)
		class UPawnNoiseEmitterComponent* PlayerNoiseEmitter;

};
