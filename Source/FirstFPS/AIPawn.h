// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PawnMovementComponent.h"
#include "AIController.h"
#include "TPMovementComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "AIPawn.generated.h"

UCLASS()
class FIRSTFPS_API AAIPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIPawn();

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

	//UPROPERTY(VisibleAnywhere)
	//	UPawnMovementComponent* TPMovement;

	UPROPERTY()
		UTPMovementComponent* TPMovement;

	UPROPERTY()
		UBehaviorTree* TPBehaviorTree;

};