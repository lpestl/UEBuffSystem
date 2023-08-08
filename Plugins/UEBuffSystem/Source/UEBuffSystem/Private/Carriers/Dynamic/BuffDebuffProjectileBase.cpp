// Fill out your copyright notice in the Description page of Project Settings.


#include "Carriers/Dynamic/BuffDebuffProjectileBase.h"

#include "Components/SphereComponent.h"
#include "Effects/BuffDebuffEffectBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interfaces/IBuffReceiver.h"


// Sets default values
ABuffDebuffProjectileBase::ABuffDebuffProjectileBase()
{
	if (CollisionComp)
	{
		CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
		
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

void ABuffDebuffProjectileBase::Init(UBuffDebuffCarrierParamsBase* InCarrierParams)
{
	Super::Init(InCarrierParams);

	if (auto ProjectileParams = Cast<UBuffDebuffProjectileParams>(InCarrierParams))
	{
		InitialLifeSpan = ProjectileParams->LifeTime;

		ProjectileMovement->InitialSpeed = ProjectileParams->Speed;
		ProjectileMovement->MaxSpeed = ProjectileParams->Speed;

		bNeedActivateByEndPlay = ProjectileParams->bIsActivateByEndOfLife;
	}
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

		// If hitting actor implement IBuffReceiver interface
		if (OtherActor->GetClass()->ImplementsInterface(UBuffReceiver::StaticClass()))
		{
			// Spawn child carriers (if is not empty)
			SpawnChildCarriers();

			// Apply effects on hitting actor
			TArray<AActor *> Targets;
			Targets.Add(OtherActor);
			ApplyEffects(Targets);

			if (auto ProjectileParams = Cast<UBuffDebuffProjectileParams>(CarrierParams))
			{
				bNeedActivateByEndPlay = false;
			}
			// After the effect spawns - the carrier object is no longer needed and can be destroyed
			Destroy();
		}
	}
}

void ABuffDebuffProjectileBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (bNeedActivateByEndPlay)
	{
		// Spawn child carriers (if is not empty)
		SpawnChildCarriers();
	}
}

