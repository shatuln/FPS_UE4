// Fill out your copyright notice in the Description page of Project Settings.


#include "AICharacter.h"
#include "Projectiles.h"

// Sets default values
AAICharacter::AAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TPMesh"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> TPSkeletalAsset(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin"));
	if (TPMesh) {
		TPMesh->SetSkeletalMesh(TPSkeletalAsset.Object);
		TPMesh->bCastDynamicShadow = true;
		TPMesh->CastShadow = true;
		TPMesh->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
		TPMesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
		TPMesh->SetupAttachment(RootComponent);

		static ConstructorHelpers::FObjectFinder<UAnimBlueprint> TPAnimBP(TEXT("/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP"));
		TPMesh->SetAnimInstanceClass(TPAnimBP.Object->GeneratedClass);
		//TPMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//TPMesh->SetCollisionEnabled(true);
		//TPMesh->SetSimulatePhysics(true);
	}

	TPPerception = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("TPPerception"));
	if (TPPerception) {
		UAISenseConfig_Sight* sightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));
		if (sightConfig) {
			sightConfig->SightRadius = 2000.0f;
			sightConfig->LoseSightRadius = 2500.0f;
			sightConfig->PeripheralVisionAngleDegrees = 90.0f;
			sightConfig->DetectionByAffiliation.bDetectEnemies = true;
			sightConfig->DetectionByAffiliation.bDetectNeutrals = true;
		}
		TPPerception->ConfigureSense(*sightConfig);
		TPPerception->SetDominantSense(sightConfig->GetSenseImplementation());
		TPPerception->OnPerceptionUpdated.AddDynamic(this, &AAICharacter::OnSense);
	}

	SetActorScale3D(FVector(1.3f, 1.3f, 1.3f));

	static ConstructorHelpers::FObjectFinder<UBlueprint> TPControllerBP(TEXT("/Game/Mannequin/AI/AIC_TP.AIC_TP"));
	AIControllerClass = TPControllerBP.Object->GeneratedClass;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AAICharacter::OnHit);

	HitPoints = 100;
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAICharacter::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->GetClass() == AProjectiles::StaticClass())
	{
		--HitPoints;
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "Hit Points: " + FString::FromInt(HitPoints));
		if (HitPoints < 0) {
			AIControllerClass = NULL;
			TPMesh->SetAnimInstanceClass(NULL);
			TPMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			TPMesh->SetSimulatePhysics(true);
		}
		
	//	OtherComponent->AddImpulseAtLocation(ProjectileMovement->Velocity * 100.0f, Hit.ImpactPoint);
	}
}

void AAICharacter::OnSense(const TArray<AActor*>& testActors) {
	for (auto i : testActors) {
		FVector location = i->GetActorLocation();
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Location X = " + FString::SanitizeFloat(location.X));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Location Y = " + FString::SanitizeFloat(location.Y));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Location Z = " + FString::SanitizeFloat(location.Z));
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "I see you!");
}