// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/BuffDebuffEffectBase.h"


// Sets default values
ABuffDebuffEffectBase::ABuffDebuffEffectBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABuffDebuffEffectBase::BeginPlay()
{
	Super::BeginPlay();	
}

void ABuffDebuffEffectBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	UWorld* const World = GetWorld();
	if (World != nullptr)
	{
		World->GetTimerManager().ClearTimer(CycleTimerHandle);
	}
	CancelEffect();
}

void ABuffDebuffEffectBase::ApplyEffect_Implementation()
{
	// Implement in child class
}

void ABuffDebuffEffectBase::CancelEffect_Implementation()
{
	// Implement in child class
}

// Called every frame
void ABuffDebuffEffectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuffDebuffEffectBase::Init(const FBuffDataTableRow& InBuffData)
{
	BuffData = InBuffData;
	
	SetLifeSpan(BuffData.LifeTimeEffect);

	if (BuffData.ImpactCycleTime > 0.f)
	{
		UWorld* const World = GetWorld();
		if (World != nullptr)
		{
			World->GetTimerManager().SetTimer(CycleTimerHandle, this, &ABuffDebuffEffectBase::ApplyEffect, BuffData.ImpactCycleTime, true);
		}
	}
}

