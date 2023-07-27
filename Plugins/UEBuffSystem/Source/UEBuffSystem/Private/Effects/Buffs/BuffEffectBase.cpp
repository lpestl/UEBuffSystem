// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/Buffs/BuffEffectBase.h"


// Sets default values
ABuffEffectBase::ABuffEffectBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABuffEffectBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuffEffectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

