// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffDebuffEffectBase.h"
#include "OneTimeDamageEffect.generated.h"

UCLASS()
class UEBUFFSYSTEM_API AOneTimeDamageEffect : public ABuffDebuffEffectBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AOneTimeDamageEffect();

	virtual void Init(const FBuffDataTableRow& InBuffData) override;

	virtual void ApplyEffect_Implementation() override;
protected:
	UPROPERTY()
	TArray<AActor *> OverlappingActors;
};
