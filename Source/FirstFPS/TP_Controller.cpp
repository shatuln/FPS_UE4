// Fill out your copyright notice in the Description page of Project Settings.

#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "TP_Controller.h"

ATP_Controller::ATP_Controller(FObjectInitializer const& object_initializer)
{
	TPPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("TPPerception"));
	if (TPPerception) {
		UAISenseConfig_Sight* sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
		if (sightConfig) {
			sightConfig->SightRadius = 2000.0f;
			sightConfig->LoseSightRadius = 2500.0f;
			sightConfig->PeripheralVisionAngleDegrees = 45.0f;
			sightConfig->DetectionByAffiliation.bDetectEnemies = true;
			sightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		}
		TPPerception->ConfigureSense(*sightConfig);
		TPPerception->SetDominantSense(sightConfig->GetSenseImplementation());
		TPPerception->OnPerceptionUpdated.AddDynamic(this, &ATP_Controller::OnSense);

		UAISenseConfig_Hearing* TPHearingPerception = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("HearingConfig"));
		if (TPHearingPerception) {
			TPHearingPerception->HearingRange = 500.0f;
			TPHearingPerception->LoSHearingRange = 600.0f;
			TPHearingPerception->SetMaxAge(5.0f);
			TPHearingPerception->DetectionByAffiliation.bDetectEnemies = true;
			TPHearingPerception->DetectionByAffiliation.bDetectNeutrals = true;
			//TPHearingPerception->bUseLoSHearing = true;
		}
		TPPerception->ConfigureSense(*TPHearingPerception);
		TPPerception->SetDominantSense(TPHearingPerception->GetSenseImplementation());
		TPPerception->OnPerceptionUpdated.AddDynamic(this, &ATP_Controller::OnSense);
	}

	//SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent")));

	//TPPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("TPPerception"));
}

void ATP_Controller::BeginPlay() 
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Hello from Controller");
}

void ATP_Controller::OnPossess(APawn* const pawn)
{
	Super::OnPossess(pawn);
}

void ATP_Controller::OnSense(const TArray<AActor*>& testActors) {
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, "Sensing");
	for (auto i : testActors) {
		FVector location = i->GetActorLocation();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Location X = " + FString::SanitizeFloat(location.X));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Location Y = " + FString::SanitizeFloat(location.Y));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Location Z = " + FString::SanitizeFloat(location.Z));

		MoveToLocation(location);
	}

}