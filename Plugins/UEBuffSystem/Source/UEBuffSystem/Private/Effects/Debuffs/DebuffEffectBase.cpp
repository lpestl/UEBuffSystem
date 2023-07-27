// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/Debuffs/DebuffEffectBase.h"


// Sets default values
ADebuffEffectBase::ADebuffEffectBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADebuffEffectBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADebuffEffectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

