// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponGun.generated.h"

UCLASS()
class FIRSTFPS_API AWeaponGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
		USkeletalMeshComponent* WeaponMesh;

	const unsigned int MaxAmmoCount = 25;

	//Current ammo count
	unsigned int AmmoCount;

	//Fire function which spawns projectiles
	void Fire();

};
