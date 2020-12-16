// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FirstFPSGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTFPS_API AFirstFPSGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:

	AFirstFPSGameModeBase();

	UPROPERTY(EditAnywhere)
		FVector SpawnPoint;

	UPROPERTY(EditAnywhere)
		FRotator SpawnRotation;

	virtual void BeginPlay() override;

};
