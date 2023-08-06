// Fill out your copyright notice in the Description page of Project Settings.

#include "SpawnPoint.h"

#include "AIController.h"
#include "Enemy.h"

void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	// Actor spawn at the start without delay
	SpawnActor();
}

void ASpawnPoint::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// Remove all delegates
	Unsubscribe();

	// Clear timer
	if (GetWorld()->GetTimerManager().TimerExists(RespawnTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);
	}
	
	Super::EndPlay(EndPlayReason);
}

void ASpawnPoint::SpawnActor()
{
	if (SpawnActorClass != nullptr)
	{
		// Add owner for spawning actor
		FActorSpawnParameters ActorSpawnParameters;
		ActorSpawnParameters.Owner = this;

		// Try spawn actor
		CurrentActor = GetWorld()->SpawnActor<AActor>(SpawnActorClass, GetActorLocation(), GetActorRotation(), ActorSpawnParameters);
		if (CurrentActor != nullptr)
		{
			// Adjust rotation if it's an AI controlled character
			if (APawn *CurrentPawn = Cast<APawn>(CurrentActor))
			{
				if (AAIController *AIController = Cast<AAIController>(CurrentPawn->GetController()))
				{
					AIController->bSetControlRotationFromPawnOrientation = false;
				}

				if (auto CurrentEnemy = Cast<AEnemy>(CurrentPawn))
				{
					CurrentEnemy->Init(FEnemyCharacteristics {});
				}
			}
			
			// Subscribe on destroyed actor event
			CurrentActor->OnDestroyed.AddDynamic(this, &ASpawnPoint::OnCurrentActorDestroyed);
		}
	}
}

void ASpawnPoint::OnCurrentActorDestroyed(AActor* DestroyedActor)
{
	Unsubscribe();

	// Reset current actor ptr
	CurrentActor = nullptr;

	// Start timer until respawn
	if (RespawnTime > 0.f)
	{
		GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &ASpawnPoint::SpawnActor, RespawnTime, false);
	}
}

void ASpawnPoint::Unsubscribe()
{
	if (CurrentActor != nullptr)
	{
		CurrentActor->OnDestroyed.RemoveDynamic(this, &ASpawnPoint::OnCurrentActorDestroyed);
	}
}

