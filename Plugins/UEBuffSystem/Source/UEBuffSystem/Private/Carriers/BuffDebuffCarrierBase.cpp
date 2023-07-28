// Fill out your copyright notice in the Description page of Project Settings.


#include "Carriers/BuffDebuffCarrierBase.h"

#include "Effects/BuffDebuffEffectBase.h"
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
			UWorld* const World = GetWorld();
			if (World != nullptr)
			{
				const FRotator SpawnRotation = GetActorRotation();
				const FVector SpawnLocation = GetActorLocation();

				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

				UClass *EffectClass = BuffData.EffectClass.LoadSynchronous();
				if (EffectClass != nullptr)
				{
					auto Bullet = World->SpawnActor<ABuffDebuffEffectBase>(EffectClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
					Bullet->Init(BuffData);
				}
			}
		}
	}
}

