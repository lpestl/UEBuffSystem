// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "DrawDebugHelpers.h"
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
	CurrentCharacteristics = InCharacteristics;

	// Apply speed
	if (IsValid(GetCharacterMovement()))
	{
		GetCharacterMovement()->MaxWalkSpeed = CurrentCharacteristics.BaseMovementSpeed;

		if ((bIsRandomCharacteristics) && (AllowedSpeed.Num() > 0))
		{
			int32 Index = FMath::RandRange(0, AllowedSpeed.Num() - 1);
			GetCharacterMovement()->MaxWalkSpeed = AllowedSpeed[Index];
		}
	}

	// Apply color
	if (bIsRandomCharacteristics && AllowedColors.Num() > 0)
	{
		int32 Index = FMath::RandRange(0, AllowedColors.Num() - 1);
		ChangeColor(AllowedColors[Index]);
	}
	else
	{
		ChangeColor(CurrentCharacteristics.Color);
	}

	// Apply health
	if (bIsRandomCharacteristics && AllowedHealth.Num() > 0)
	{		
		int32 Index = FMath::RandRange(0, AllowedHealth.Num() - 1);
		CurrentHealth = AllowedHealth[Index];
	}
	else
	{
		CurrentHealth = CurrentCharacteristics.Health;
	}

	// Apply scale
	if (bIsRandomCharacteristics)
	{
		float ScaleMultiplier = FMath::FRandRange(0.6f, 1.5f);		
		SetActorScale3D(GetActorScale3D() * ScaleMultiplier);
	}
	else
	{
		SetActorScale3D(GetActorScale3D() * CurrentCharacteristics.ScaleMultiplier);
	}
	
	if (OnEnemyInitialized.IsBound())
	{
		OnEnemyInitialized.Broadcast();
	}
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy::BuffImpact_Implementation(UClass* InEffectClass)
{
	IBuffReceiver::BuffImpact_Implementation(InEffectClass);

	// if (const FGunsDataRow* GameBuffData = Cast<FGunsDataRow>(InBuffData))
	// {
	// 	if (GameBuffData->HealthImpactValue > 0)
	// 	{
	// 		TakeHeal(GameBuffData->HealthImpactValue);
	// 	}
	// 	else
	// 	{
	// 		TakeDamage(FMath::Abs(GameBuffData->HealthImpactValue));
	// 	}
	//
	// 	AddSpeed(GameBuffData->SpeedImpactValue);
	// }
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Simplified enemy movement logic.
	// It is correct to implement this logic in the AIController class,
	// but to keep it simple and fast, let's leave it here!

	// Always moving forward
	MoveForward(1.f);

	// If the enemy ran into an obstacle, then turn it clockwise until the speed becomes normal.

	//if (FMath::Abs(CurrentEnemy->GetVelocity().Size()) < 10.f)
	{
		// FHitResult will hold all data returned by our line collision query
		FHitResult Hit;
		FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * 200.0f;

		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(this);

		GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), TraceEnd, ECollisionChannel::ECC_MAX, QueryParams);

// #if WITH_EDITOR
// 		DrawDebugLine(GetWorld(), GetActorLocation(), TraceEnd, Hit.bBlockingHit ? FColor::Red : FColor::Green, false, 0.1f, 0, 1.0f);
// 		//UE_LOG(LogTemp, Log, TEXT("Tracing line: %s to %s"), *GetActorLocation().ToCompactString(), *TraceEnd.ToCompactString());
// #endif
	
		// If the trace hit something, bBlockingHit will be true,
		// and its fields will be filled with detailed info about what was hit
		if (Hit.bBlockingHit)
		{
			UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());

			float AngleRotate = FMath::RandRange(0, 360);
			GetController()->SetControlRotation(
				FRotator(
					GetController()->GetControlRotation().Pitch,
					AngleRotate,
					GetController()->GetControlRotation().Roll));
		}
	}
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
	if (GetCharacterMovement()->MaxWalkSpeed + InAddingValue >= 0)
	{
		GetCharacterMovement()->MaxWalkSpeed += InAddingValue;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = 0;
	}

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