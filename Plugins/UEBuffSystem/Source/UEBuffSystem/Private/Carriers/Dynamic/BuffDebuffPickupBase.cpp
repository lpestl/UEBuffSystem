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
	
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	if (CollisionComp)
	{
		AddInstanceComponent(CollisionComp);

		// Default collision settings (CDO settings settings for component)
		CollisionComp->InitSphereRadius(50.0f);
		CollisionComp->BodyInstance.SetCollisionProfileName("ActivateCollision");
		CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
		CollisionComp->CanCharacterStepUpOn = ECB_No;

		// Subscribe to the "OnBeginOverlap" method
		CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &ABuffDebuffPickupBase::OnActivateCollisionComponentBeginOverlap);
		
		CollisionComp->SetupAttachment(RootComponent);
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
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			const FRotator SpawnRotation = GetActorRotation();
			const FVector SpawnLocation = GetActorLocation();

			// Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			UClass *EffectClass = BuffData.EffectClass.LoadSynchronous();
			if (EffectClass != nullptr)
			{
				// When an effect spawns, it automatically impacts objects
				auto Effect = World->SpawnActor<ABuffDebuffEffectBase>(EffectClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
				Effect->Init(BuffData);
			}

			// After the effect spawns - the carrier object is no longer needed and can be destroyed
			Destroy();
		}
	}
}