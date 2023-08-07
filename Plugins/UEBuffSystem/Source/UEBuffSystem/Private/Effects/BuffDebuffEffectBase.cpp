// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/BuffDebuffEffectBase.h"

#include "Carriers/BuffDebuffCarrierBase.h"
#include "Interfaces/IBuffReceiver.h"

void UBuffDebuffEffectBase::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* const World = GetWorld();
	if ((World != nullptr) && (EffectParams != nullptr))
	{
		World->GetTimerManager().SetTimerForNextTick(this, &UBuffDebuffEffectBase::Impact);
		
		if (EffectParams->bIsCycle)
		{
			World->GetTimerManager().SetTimer(EffectCycleTimerHandle, this, &UBuffDebuffEffectBase::Impact, EffectParams->CycleTime, true);
		}

		if (EffectParams->LifeTime > 0.f)
		{
			World->GetTimerManager().SetTimer(LifeTimerHandle, this, &UBuffDebuffEffectBase::DestroyEffect, EffectParams->LifeTime, false);
		}
	}
}

void UBuffDebuffEffectBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UWorld* const World = GetWorld();
	if ((World != nullptr) && (EffectParams != nullptr))
	{
		if (EffectParams->bIsCancelableEffect)
		{
			CancelImpact();
		}
		
		if (World->GetTimerManager().TimerExists(EffectCycleTimerHandle))
		{
			World->GetTimerManager().ClearTimer(EffectCycleTimerHandle);
		}

		if (World->GetTimerManager().TimerExists(LifeTimerHandle))
		{
			World->GetTimerManager().ClearTimer(LifeTimerHandle);
		}
	}

	SpawnChildCarriers();

	if (GetOwner() != nullptr)
	{
		TArray<AActor *> Targets;
		Targets.Add(GetOwner());
		ApplyEffects(Targets);
	}
	
	Super::EndPlay(EndPlayReason);
}

void UBuffDebuffEffectBase::Init(UBuffDebuffEffectParamsBase* InParams)
{
	EffectParams = InParams;
}

void UBuffDebuffEffectBase::DestroyEffect()
{
	DestroyComponent();
}

void UBuffDebuffEffectBase::SpawnChildCarriers()
{
	if (EffectParams != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			for (auto&& SpawningCarrierParams : EffectParams->ChildCarriers)
			{
				// Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;

				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				ActorSpawnParams.Owner = GetOwner();

				if (GetOwner() != nullptr)
				{
					// Spawn carrier actor
					if (auto ChildCarrier = World->SpawnActor<ABuffDebuffCarrierBase>(SpawningCarrierParams->CarrierClass, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), ActorSpawnParams))
					{
						// Initialize 
						ChildCarrier->Init(SpawningCarrierParams);
					}
				}
			}
		}
	}
}

void UBuffDebuffEffectBase::ApplyEffects(const TArray<AActor*>& InTargets)
{
	if (EffectParams != nullptr)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			for (auto&& InTarget : InTargets)
			{
				if (InTarget->GetClass()->ImplementsInterface(UBuffReceiver::StaticClass()))
				{
					for (auto&& SpawningEffectParams : EffectParams->ChildEffects)
					{
						InTarget->AddComponent(SpawningEffectParams->Name, false, FTransform {}, SpawningEffectParams->EffectClass);
					}
				}
			}
		}
	}
}

FName UBuffDebuffEffectBase::GetBuffEffectName()
{
	if (EffectParams != nullptr)
	{
		return EffectParams->Name;
	}
	
	return FName(TEXT("Buff/Debuff Base"));
}
