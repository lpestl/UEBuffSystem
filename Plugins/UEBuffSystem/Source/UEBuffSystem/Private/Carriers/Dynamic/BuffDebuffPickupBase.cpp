// Fill out your copyright notice in the Description page of Project Settings.


#include "Carriers/Dynamic/BuffDebuffPickupBase.h"

#include "Components/SphereComponent.h"
#include "Effects/BuffDebuffEffectBase.h"
#include "Interfaces/IBuffReceiver.h"


// Sets default values
ABuffDebuffPickupBase::ABuffDebuffPickupBase()
{
	// Set as root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	
	if (CollisionComp)
	{
		CollisionComp->BodyInstance.SetCollisionProfileName("ActivateCollision");
		
		// Subscribe to the "OnBeginOverlap" method
		CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ABuffDebuffPickupBase::OnActivateCollisionComponentBeginOverlap);
		
		CollisionComp->SetupAttachment(RootComponent);
	}
}

void ABuffDebuffPickupBase::Init(UBuffDebuffCarrierParamsBase* InCarrierParams)
{
	Super::Init(InCarrierParams);

	if (CarrierParams != nullptr)
	{
		if (auto PickupParams = Cast<UBuffDebuffPickupParams>(CarrierParams))
		{
			if (PickupParams->LifeTime > 0.f)
			{
				InitialLifeSpan = PickupParams->LifeTime;
			}
		}
	}
}

void ABuffDebuffPickupBase::OnActivateCollisionComponentBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	// If Overlapping actor valid AND the actor implements the "Buff Receiver" interface
	if ((OtherActor != nullptr) && (OtherActor->GetClass()->ImplementsInterface(UBuffReceiver::StaticClass())))
	{
		// Spawn child carriers (if is not empty)
		SpawnChildCarriers();

		// Apply effects on hitting actor
		TArray<AActor *> Targets;
		Targets.Add(OtherActor);
		ApplyEffects(Targets);
		
		// After the effect spawns - the carrier object is no longer needed and can be destroyed
		if (CarrierParams != nullptr)
		{
			if (auto PickupParams = Cast<UBuffDebuffPickupParams>(CarrierParams))
			{
				if (PickupParams->bIsDestroyAfterOverlap)
				{
					Destroy();
				}
			}
		}
	}
}
