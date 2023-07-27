// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effects/BuffDebuffEffectBase.h"
#include "BuffEffectBase.generated.h"

UCLASS()
class UEBUFFSYSTEM_API ABuffEffectBase : public ABuffDebuffEffectBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuffEffectBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
