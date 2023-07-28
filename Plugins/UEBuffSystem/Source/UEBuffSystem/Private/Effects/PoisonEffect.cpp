// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/PoisonEffect.h"

#include "Interfaces/IBuffReceiver.h"


// Sets default values
APoisonEffect::APoisonEffect()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APoisonEffect::Init(const FBuffDataTableRow& InBuffData)
{
	Super::Init(InBuffData);

	CollisionComp->SetSphereRadius(BuffData.EffectRadius);
	
	CollisionComp->GetOverlappingActors(OverlappingActors, UBuffReceiver::StaticClass());
	ApplyEffect();
}

void APoisonEffect::ApplyEffect_Implementation()
{
	Super::ApplyEffect_Implementation();

	for (auto AffectedActor : OverlappingActors)
	{
		if (!IsValid(AffectedActor))
		{
			continue;
		}
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

// Called every frame
void APoisonEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

