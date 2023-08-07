#include "Carriers/BuffDebuffCarrierBase.h"

#include "Effects/BuffDebuffEffectBase.h"
#include "Interfaces/IBuffReceiver.h"

void ABuffDebuffCarrierBase::Init(UBuffDebuffCarrierParamsBase *InCarrierParams)
{
	CarrierParams = InCarrierParams;
}

void ABuffDebuffCarrierBase::SpawnChildCarriers()
{
	if (CarrierParams != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			for (auto&& SpawningCarrierParams : CarrierParams->ChildCarriers)
			{
				// Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;

				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				ActorSpawnParams.Owner = GetOwner();

				// Spawn carrier actor
				if (auto ChildCarrier = World->SpawnActor<ABuffDebuffCarrierBase>(SpawningCarrierParams->CarrierClass, GetActorLocation(), GetActorRotation(), ActorSpawnParams))
				{
					// Initialize 
					ChildCarrier->Init(SpawningCarrierParams);
				}
			}
		}
	}
}

void ABuffDebuffCarrierBase::ApplyEffects(const TArray<AActor*>& InTargets)
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		for (auto&& InTarget : InTargets)
		{
			if (InTarget->GetClass()->ImplementsInterface(UBuffReceiver::StaticClass()))
			{
				for (auto&& SpawningEffectParams : CarrierParams->ChildEffects)
				{
					InTarget->AddComponent(SpawningEffectParams->Name, false, FTransform {}, SpawningEffectParams->EffectClass);
				}
			}
		}
	}
}
