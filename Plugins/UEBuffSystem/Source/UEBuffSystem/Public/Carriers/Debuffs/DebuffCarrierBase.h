// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Carriers/BuffDebuffCarrierBase.h"
#include "DebuffCarrierBase.generated.h"

UCLASS()
class UEBUFFSYSTEM_API ADebuffCarrierBase : public ABuffDebuffCarrierBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADebuffCarrierBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
