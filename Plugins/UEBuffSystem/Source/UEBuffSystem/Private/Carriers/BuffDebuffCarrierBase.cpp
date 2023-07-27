// Fill out your copyright notice in the Description page of Project Settings.


#include "Carriers/BuffDebuffCarrierBase.h"


// Sets default values
ABuffDebuffCarrierBase::ABuffDebuffCarrierBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABuffDebuffCarrierBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuffDebuffCarrierBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

