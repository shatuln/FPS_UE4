// Copyright Epic Games, Inc. All Rights Reserved.


#include "FirstFPSGameModeBase.h"
#include "AICharacter.h"
#include "PlayerCharacter.h"

AFirstFPSGameModeBase::AFirstFPSGameModeBase() {
	SpawnPoint.X = 100.0f;
	SpawnPoint.Y = 100.0f;
	SpawnPoint.Z = 600.0f;

	SpawnRotation.Pitch = 0.0f;
	SpawnRotation.Roll = 0.0f;
	SpawnRotation.Yaw = 0.0f;

	DefaultPawnClass = APlayerCharacter::StaticClass();
}

void AFirstFPSGameModeBase::BeginPlay() {

	Super::BeginPlay();

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.Owner = this;
	for (int i = 0; i < 1; ++i) {
		//GetWorld()->SpawnActor<AAICharacter>(AAICharacter::StaticClass(), SpawnPoint, SpawnRotation, ActorSpawnParams);
	}
}