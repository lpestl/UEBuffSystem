#include "Carriers/BuffDebuffCarrierBase.h"

#include "Effects/BuffDebuffEffectBase.h"
#include "Interfaces/IBuffReceiver.h"

void ABuffDebuffCarrierBase::SpawnChildCarriers()
{
	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		for (auto&& SpawningCarrier : SpawningCarriers)
		{
			// Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;

			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			ActorSpawnParams.Owner = GetOwner();
			ActorSpawnParams.Template = SpawningCarrier;
			
			auto ChildCarrier = World->SpawnActor<ABuffDebuffCarrierBase>(SpawningCarrier->GetClass(), GetActorLocation(), GetActorRotation(), ActorSpawnParams);
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
				for (auto&& SpawningEffect : SpawningEffects)
				{
					InTarget->AddComponent(SpawningEffect->GetBuffEffectName(), false, FTransform {}, SpawningEffect);
				}
			}
		}
	}
}
