// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawnPoint.h"

#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "Enemy.h"
#include "GameFramework/PawnMovementComponent.h"


// Sets default values
AEnemySpawnPoint::AEnemySpawnPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// set default pawn class to our Blueprinted character
	// TODO: Hard code - is bad! Move on config
	static ConstructorHelpers::FClassFinder<APawn> EnemyPawnClassFinder(TEXT("/Game/Blueprints/BP_Enemy"));
	EnemyClass = EnemyPawnClassFinder.Class;
}

// Called when the game starts or when spawned
void AEnemySpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	SpawnEnemy();
}

bool AEnemySpawnPoint::SpawnEnemy()
{
	// Add owner for enemy
	FActorSpawnParameters EnemySpawnParameters;
	EnemySpawnParameters.Owner = this;

	// Try spawn enemy
	if (AEnemy *SpawnedEnemy = GetWorld()->SpawnActor<AEnemy>(EnemyClass, GetTransform().GetLocation(), GetTransform().GetRotation().Rotator(), EnemySpawnParameters))
	{
		CurrentEnemy = SpawnedEnemy;
		if (auto AIController = Cast<AAIController>(CurrentEnemy->GetController()))
		{
			AIController->bSetControlRotationFromPawnOrientation = false;
		}
		// Subscribe on destroyed enemy event
		SpawnedEnemy->OnDestroyed.AddDynamic(this, &AEnemySpawnPoint::OnCurrentEnemyDestroyed);

		// Successful spawn
		return true;
	}

	// spawn failed
	return false;
}

void AEnemySpawnPoint::OnCurrentEnemyDestroyed(AActor* DestroyedActor)
{
	if (AEnemy *DestroyedEnemy = Cast<AEnemy>(DestroyedActor))
	{
		// Unsubscribe
		DestroyedEnemy->OnDestroyed.RemoveDynamic(this, &AEnemySpawnPoint::OnCurrentEnemyDestroyed);
	}

	// Respawn next enemy
	SpawnEnemy();
}

// Called every frame
void AEnemySpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Simplified enemy movement logic.
	// It is correct to implement this logic in the AIController class,
	// but to keep it simple and fast, let's leave it here!

	if (IsValid(CurrentEnemy))
	{
		// Always moving forward
		CurrentEnemy->MoveForward(1.f);

		// If the enemy ran into an obstacle, then turn it clockwise until the speed becomes normal.

		//if (FMath::Abs(CurrentEnemy->GetVelocity().Size()) < 10.f)
		{
			// FHitResult will hold all data returned by our line collision query
			FHitResult Hit;
			FVector TraceEnd = CurrentEnemy->GetActorLocation() + CurrentEnemy->GetActorForwardVector() * 200.0f;

			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(this);
			QueryParams.AddIgnoredActor(CurrentEnemy);

			GetWorld()->LineTraceSingleByChannel(Hit, CurrentEnemy->GetActorLocation(), TraceEnd, ECollisionChannel::ECC_MAX, QueryParams);

#if WITH_EDITOR
			DrawDebugLine(GetWorld(), CurrentEnemy->GetActorLocation(), TraceEnd, Hit.bBlockingHit ? FColor::Red : FColor::Green, false, 0.1f, 0, 1.0f);
			//UE_LOG(LogTemp, Log, TEXT("Tracing line: %s to %s"), *GetActorLocation().ToCompactString(), *TraceEnd.ToCompactString());
#endif
		
			// If the trace hit something, bBlockingHit will be true,
			// and its fields will be filled with detailed info about what was hit
			if (Hit.bBlockingHit)
			{
				UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());

				float AngleRotate = FMath::RandRange(0, 360);
				CurrentEnemy->GetController()->SetControlRotation(
					FRotator(
						CurrentEnemy->GetController()->GetControlRotation().Pitch,
						AngleRotate,
						CurrentEnemy->GetController()->GetControlRotation().Roll));
			}
		}
	}

}

