// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Perception/AIPerceptionComponent.h"
//#include "Perception/AISenseConfig.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Components/CapsuleComponent.h"
#include "AIController.h"
#include "AICharacter.generated.h"

UCLASS()
class FIRSTFPS_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
		USkeletalMeshComponent* TPMesh;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere)
		int HitPoints;

	UPROPERTY()
		UAIPerceptionComponent* TPPerception;

	UFUNCTION()
		void OnSense(const TArray<AActor*>& testActors);
};
