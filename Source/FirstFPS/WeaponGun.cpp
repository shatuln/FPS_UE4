// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponGun.h"

// Sets default values
AWeaponGun::AWeaponGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ActualWeaponMesh(TEXT("/Game/FirstPerson/FPWeapon/Mesh/SK_FPGun.SK_FPGun"));
	if (WeaponMesh) {
		WeaponMesh->SetSkeletalMesh(ActualWeaponMesh.Object);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "This is message from weapon");

}

// Called when the game starts or when spawned
void AWeaponGun::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void AWeaponGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "This is message from weapon");
}

