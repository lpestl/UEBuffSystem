// Fill out your copyright notice in the Description page of Project Settings.


#include "Carriers/BuffDebuffCarrierBase.h"

#include "Interfaces/IBuffReceiver.h"


// Sets default values
ABuffDebuffCarrierBase::ABuffDebuffCarrierBase()
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");

	CollisionComp->OnComponentHit.AddDynamic(this, &ABuffDebuffCarrierBase::OnHit);		// set up a notification for when this component hits something blocking

	// Set as root component
	RootComponent = CollisionComp;
}

void ABuffDebuffCarrierBase::Init(const FBuffDataTableRow& InData)
{
	BuffData = InData;
}

void ABuffDebuffCarrierBase::OnHit(
	UPrimitiveComponent* HitComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	FVector NormalImpulse,
	const FHitResult& Hit)
{
	if (OtherActor != nullptr)
	{
		if (OtherActor->GetClass()->ImplementsInterface(UBuffReceiver::StaticClass()))
		{
			if (BuffData.HealthImpactValue != 0.f)
			{
				IBuffReceiver::Execute_ImpactHealth(OtherActor, -100);
			}
		}
	}
}

