// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"

// Sets default values
AAIPawn::AAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TPMesh"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> TPSkeletalAsset(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin"));
	if (TPMesh) {
		TPMesh->SetSkeletalMesh(TPSkeletalAsset.Object);
		TPMesh->bCastDynamicShadow = true;
		TPMesh->CastShadow = true;

		static ConstructorHelpers::FObjectFinder<UAnimBlueprint> TPAnimBP(TEXT("/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP"));
		TPMesh->SetAnimInstanceClass(TPAnimBP.Object->GeneratedClass);
		//TPMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//TPMesh->SetCollisionEnabled(true);
		//TPMesh->SetSimulatePhysics(true);
		RootComponent = TPMesh;
	}

	TPMovement = CreateDefaultSubobject<UTPMovementComponent>(TEXT("TPMovement"));

	if (TPMovement) {
		TPMovement->SetUpdatedComponent(RootComponent);
	}


	//static ConstructorHelpers::FObjectFinder<UBehaviorTree> TPBehaviorTreeAsset(TEXT("/Game/Mannequin/AI/BT_TP.BT_TP"));
	//TPBehaviorTree = TPBehaviorTreeAsset.Object;

	//TPController = CreateDefaultSubobject<ATP_Controller>(TEXT("TPController"));
	
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();
	
	
	//TPController->RunBehaviorTree(TPBehaviorTree);

}

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAIPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

