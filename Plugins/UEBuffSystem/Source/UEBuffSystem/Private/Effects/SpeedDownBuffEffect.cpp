// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/SpeedDownBuffEffect.h"

#include "Interfaces/IBuffReceiver.h"


// Sets default values
ASpeedDownBuffEffect::ASpeedDownBuffEffect()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASpeedDownBuffEffect::Init(const FBuffDataTableRow& InBuffData)
{
	Super::Init(InBuffData);

	CollisionComp->SetSphereRadius(BuffData.EffectRadius);

	CollisionComp->GetOverlappingActors(OverlappingActors, UBuffReceiver::StaticClass());
	ApplyEffect();
}

void ASpeedDownBuffEffect::ApplyEffect_Implementation()
{
	Super::ApplyEffect_Implementation();

	for (auto AffectedActor : OverlappingActors)
	{
		if (AffectedActor->GetClass()->ImplementsInterface(UBuffReceiver::StaticClass()))
		{
			if (BuffData.HealthImpactValue != 0.f)
			{
				IBuffReceiver::Execute_ImpactHealth(AffectedActor, BuffData.HealthImpactValue);
			}

			if (BuffData.SpeedImpactValue != 0.f)
			{
				IBuffReceiver::Execute_ImpactSpeed(AffectedActor, BuffData.SpeedImpactValue);
			}
		}
	}
}

void ASpeedDownBuffEffect::CancelEffect_Implementation()
{
	Super::CancelEffect_Implementation();

	for (auto AffectedActor : OverlappingActors)
	{
		if (AffectedActor != nullptr)
		{
			if (AffectedActor->GetClass()->ImplementsInterface(UBuffReceiver::StaticClass()))
			{
				if (BuffData.HealthImpactValue != 0.f)
				{
					IBuffReceiver::Execute_ImpactHealth(AffectedActor, -BuffData.HealthImpactValue);
				}

				if (BuffData.SpeedImpactValue != 0.f)
				{
					IBuffReceiver::Execute_ImpactSpeed(AffectedActor, -BuffData.SpeedImpactValue);
				}
			}
		}
	}
}

// Called when the game starts or when spawned
void ASpeedDownBuffEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpeedDownBuffEffect::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	CancelEffect();
}

