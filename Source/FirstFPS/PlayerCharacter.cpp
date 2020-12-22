// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/PawnNoiseEmitterComponent.h"
#include "PlayerCharacter.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	if (FPSCameraComponent) {
		FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
		FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
		FPSCameraComponent->bUsePawnControlRotation = true;
	}
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> ArmsVisualMesh(TEXT("/Game/FirstPerson/Character/Mesh/SK_Mannequin_Arms.SK_Mannequin_Arms"));
	if (FPSMesh) {
		FPSMesh->SetSkeletalMesh(ArmsVisualMesh.Object);
		FPSMesh->SetOnlyOwnerSee(true);
		FPSMesh->SetupAttachment(FPSCameraComponent); 
		FPSMesh->bCastDynamicShadow = false;
		FPSMesh->CastShadow = false;
		FVector NewLocation = FVector(-3.0f, 5.0f, -150.0f);
		FRotator NewRotation = FRotator(0.0f, -15.0f, 0.0f);
		FPSMesh->SetRelativeLocationAndRotation(NewLocation, NewRotation);

		static ConstructorHelpers::FObjectFinder<UAnimBlueprint> FPSAnimBP(TEXT("/Game/FirstPerson/Animations/FirstPerson_AnimBP.FirstPerson_AnimBP"));
		FPSMesh->SetAnimInstanceClass(FPSAnimBP.Object->GeneratedClass);
	}

	TPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ThirdPersonMesh"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> TPVisualMesh(TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin"));
	if (TPMesh) {
		TPMesh->SetSkeletalMesh(TPVisualMesh.Object);
		TPMesh->SetupAttachment(FPSCameraComponent);
		TPMesh->bCastHiddenShadow = true;
		TPMesh->SetOwnerNoSee(true);
		TPMesh->bCastDynamicShadow = true;
		TPMesh->CastShadow = true;
		FVector NewLocation = FVector(0.0f, 0.0f, -180.0f);
		FRotator NewRotation = FRotator(0.0f, -90.0f, 0.0f);
		TPMesh->SetRelativeLocationAndRotation(NewLocation, NewRotation);

		static ConstructorHelpers::FObjectFinder<UAnimBlueprint> TPAnimBP(TEXT("/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP"));
		TPMesh->SetAnimInstanceClass(TPAnimBP.Object->GeneratedClass);
	}

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponVisualMesh(TEXT("/Game/FirstPerson/FPWeapon/Mesh/SK_FPGun.SK_FPGun"));
	if (WeaponMesh) {
		WeaponMesh->SetSkeletalMesh(WeaponVisualMesh.Object);
		//WeaponMesh->SetupAttachment(FPSMesh);

		WeaponFrontLocation = CreateDefaultSubobject<USceneComponent>(TEXT("WeaponFrontLocation"));
		if (WeaponFrontLocation) {
			WeaponFrontLocation->SetupAttachment(WeaponMesh);
			WeaponFrontLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
		}
	}

	PlayerNoiseEmitter = CreateDefaultSubobject<UPawnNoiseEmitterComponent>(TEXT("NoiseEmitter"));
	PlayerNoiseEmitter->SetAutoActivate(true);

	static ConstructorHelpers::FObjectFinder<UAnimMontage> FireMontage(TEXT("/Game/FirstPerson/Animations/FirstPersonFire_Montage.FirstPersonFire_Montage"));
	FireAnimation = FireMontage.Object;

	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;

	// The owning player doesn't see the regular (third-person) body mesh.
	//GetMesh()->SetOwnerNoSee(true);
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	WeaponMesh->AttachToComponent(FPSMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	WeaponAmmo = WeaponAmmoMax;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PlayerNoiseEmitter->MakeNoise(this, 1.0f, GetActorLocation());

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Set up buttons bindings.
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerCharacter::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerCharacter::StopFire);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayerCharacter::Reload);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &APlayerCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &APlayerCharacter::StopCrouch);

	PlayerInputComponent->BindAction("Boost", IE_Pressed, this, &APlayerCharacter::StartBoosting);
	PlayerInputComponent->BindAction("Boost", IE_Released, this, &APlayerCharacter::StopBoosting);

	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	// Set up "look" bindings.
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::AddControllerPitchInput);

}

void APlayerCharacter::MoveForward(float Value)
{
	// Find out which way is "forward" and record that the player wants to move that way.
	//PlayerNoiseEmitter->MakeNoise(this, 1.0f, GetActorLocation());
	MakeNoise();
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	// Find out which way is "right" and record that the player wants to move that way.
	//PlayerNoiseEmitter->MakeNoise(this, 1.0f, GetActorLocation());
	MakeNoise();
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void APlayerCharacter::StartCrouch() {
	Crouch(1);
}

void APlayerCharacter::StopCrouch() {
	UnCrouch(1);
}

void APlayerCharacter::StartBoosting() {
	GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed * 2;
}

void APlayerCharacter::StopBoosting() {
	GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed / 2;
}

void APlayerCharacter::Fire() {

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, "This is message from weapon");
	
	OnFireTimer();
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &APlayerCharacter::OnFireTimer, 0.1f, true);
}

void APlayerCharacter::Reload() {
	WeaponAmmo = 0;
	GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &APlayerCharacter::OnReloadTimer, 2.0f, false);
}

void APlayerCharacter::StopFire() {
	GetWorldTimerManager().ClearTimer(FireTimerHandle);
}

void APlayerCharacter::OnReloadTimer() {
	WeaponAmmo = WeaponAmmoMax;
}

void APlayerCharacter::OnFireTimer() {
	if (WeaponAmmo < 1) {
		if (!GetWorldTimerManager().IsTimerActive(ReloadTimerHandle)) {
			GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &APlayerCharacter::OnReloadTimer, 2.0f, false);
		}
	}
	else {
		if (FireAnimation != NULL)
		{
			// Get the animation object for the arms mesh
			UAnimInstance* AnimInstance = FPSMesh->GetAnimInstance();
			if (AnimInstance != NULL)
			{
				AnimInstance->Montage_Play(FireAnimation, 1.8f);
			}
		}
		//CurrentState = FIRE_STATE;
		// Default offset from the character location for projectiles to spawn
		FVector GunOffset = FVector(100.0f, 0.0f, 10.0f);

		const FRotator SpawnRotation = GetControlRotation();
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
		const FVector SpawnLocation = WeaponFrontLocation->GetComponentLocation();

		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.Owner = this;
		ActorSpawnParams.Instigator = GetInstigator();
		//ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		// spawn the projectile at the muzzle

		GetWorld()->SpawnActor<AProjectiles>(AProjectiles::StaticClass(), SpawnLocation, SpawnRotation, ActorSpawnParams);

		--WeaponAmmo;
	}

	
}