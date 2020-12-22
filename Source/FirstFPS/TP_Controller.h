// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "TP_Controller.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTFPS_API ATP_Controller : public AAIController
{
	GENERATED_BODY()

public:
	ATP_Controller(FObjectInitializer const& object_initializer);
protected:
	virtual void BeginPlay() override;

	virtual void OnPossess(APawn* const pawn) override;

public:

	//UPROPERTY()
	//	class UBehaviorTreeComponent* BTreeComponent;
	
	//UPROPERTY()
	//	UBehaviorTree* BTree;

	//UPROPERTY()
	//	UBlackboardComponent* BBoard;

	UPROPERTY()
		UAIPerceptionComponent* TPPerception;

	//UPROPERTY()
	//	UAISenseConfig_Hearing* TPHearingPerception;


	UFUNCTION()
		void OnSense(const TArray<AActor*>& testActors);

};
