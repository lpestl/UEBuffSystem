// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
}

void AEnemy::Init(FEnemyCharacteristics InCharacteristics)
{
	InitCharacteristic = InCharacteristics;

	// Apply speed
	if (IsValid(GetCharacterMovement()))
	{
		GetCharacterMovement()->MaxWalkSpeed = InitCharacteristic.BaseMovementSpeed;
	}

	ChangeColor(InitCharacteristic.Color);

	CurrentHealth = InitCharacteristic.Health;

	SetActorScale3D(GetActorScale3D() * InitCharacteristic.ScaleMultiplier);
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemy::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		                                                                                                                                                                                                                                                                                                                                                                        const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AEnemy::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AEnemy::TakeDamage(float DamageValue)
{
	CurrentHealth -= DamageValue;

	if (OnHealthChanged.IsBound())
	{
		OnHealthChanged.Broadcast();
	}
	
	if (CurrentHealth <= 0.f)
	{
		Destroy();
	}
}

void AEnemy::TakeHeal(float HealValue)
{
	CurrentHealth += HealValue;

	if (OnHealthChanged.IsBound())
	{
		OnHealthChanged.Broadcast();
	}
}

void AEnemy::AddSpeed(float InAddingValue)
{
	GetCharacterMovement()->MaxWalkSpeed += InAddingValue;

	if (OnSpeedChanged.IsBound())
	{
		OnSpeedChanged.Broadcast();
	}
}

float AEnemy::GetCurrentHealth() const
{
	return CurrentHealth;
}

float AEnemy::GetBaseSpeed() const
{
	return GetCharacterMovement()->MaxWalkSpeed;
}


