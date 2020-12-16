// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles.h"

// Sets default values
AProjectiles::AProjectiles()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileSphere"));
	if (ProjectileSphere) {
		ProjectileSphere->InitSphereRadius(3.0f);
		ProjectileSphere->BodyInstance.SetCollisionProfileName("Projectile");
	}
	
	RootComponent = ProjectileSphere;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	if (ProjectileMovement) {
		ProjectileMovement->UpdatedComponent = ProjectileSphere;
		ProjectileMovement->InitialSpeed = 3000.f;
		ProjectileMovement->MaxSpeed = 3000.f;
		ProjectileMovement->bRotationFollowsVelocity = true;
		ProjectileMovement->bShouldBounce = true;
	}

	InitialLifeSpan = 30.0f;

	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMeshComponent"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	if (Mesh.Succeeded())
	{
		ProjectileMeshComponent->SetupAttachment(RootComponent);
		ProjectileMeshComponent->SetStaticMesh(Mesh.Object);
		ProjectileMeshComponent->SetRelativeScale3D(FVector(0.05f, 0.05f, 0.05f));
		ProjectileMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -2.5f));
	}

	ProjectileSphere->OnComponentHit.AddDynamic(this, &AProjectiles::OnHit);


}

void AProjectiles::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovement->Velocity * 10.0f, Hit.ImpactPoint);
	}

	Destroy();
}

/*
// Called when the game starts or when spawned
void AProjectiles::BeginPlay()
{
	Super::BeginPlay();
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "ProjectileCreated");
	
}

// Called every frame
void AProjectiles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/
