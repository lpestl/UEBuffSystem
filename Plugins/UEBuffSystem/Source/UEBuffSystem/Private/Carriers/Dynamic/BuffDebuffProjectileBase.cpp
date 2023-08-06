// Fill out your copyright notice in the Description page of Project Settings.


#include "Carriers/Dynamic/BuffDebuffProjectileBase.h"

#include "Components/SphereComponent.h"
#include "Effects/BuffDebuffEffectBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interfaces/IBuffReceiver.h"


// Sets default values
ABuffDebuffProjectileBase::ABuffDebuffProjectileBase()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	if (CollisionComp)
	{
		AddInstanceComponent(CollisionComp);

		// Default collision settings (CDO settings settings for component)
		CollisionComp->InitSphereRadius(5.0f);
		CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
		CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
		CollisionComp->CanCharacterStepUpOn = ECB_No;
		
		// Subscribe to the "hit" method
		CollisionComp->OnComponentHit.AddDynamic(this, &ABuffDebuffProjectileBase::OnHit);		// set up a notification for when this component hits something blocking
	}
	RootComponent = CollisionComp;
	
	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	if (ProjectileMovement)
	{
		AddInstanceComponent(ProjectileMovement);

		// Default projectile settings (CDO setting for component)
		ProjectileMovement->UpdatedComponent = CollisionComp;
		ProjectileMovement->InitialSpeed = 3000.f;
		ProjectileMovement->MaxSpeed = 3000.f;
		ProjectileMovement->bRotationFollowsVelocity = true;
		ProjectileMovement->bShouldBounce = true;
	}

	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void ABuffDebuffProjectileBase::OnHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	// If hitting the actor AND the actor implements the "Buff Receiver" interface
	if (OtherActor != nullptr)
	{
		// Add hit impulse on physics component
		if ((OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
		}

		if (OtherActor->GetClass()->ImplementsInterface(UBuffReceiver::StaticClass()))
		{
			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				const FRotator SpawnRotation = GetActorRotation();
				const FVector SpawnLocation = GetActorLocation();

				// Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				// if (EffectClass != nullptr)
				// {
				// 	// // When an effect spawns, it automatically impacts objects
				// 	// auto Effect = World->SpawnActor<ABuffDebuffEffectBase>(EffectClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
				// 	// //Effect->Init(BuffData);
				// }

				// After the effect spawns - the carrier object is no longer needed and can be destroyed
				Destroy();
			}
		}
	}
}

