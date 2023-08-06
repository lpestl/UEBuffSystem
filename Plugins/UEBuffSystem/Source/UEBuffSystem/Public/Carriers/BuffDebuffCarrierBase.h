// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuffDebuffCarrierBase.generated.h"

class UBuffDebuffEffectBase;

/*
 * Base class for buff carrier
 */
UCLASS()
class UEBUFFSYSTEM_API ABuffDebuffCarrierBase : public AActor
{
	GENERATED_BODY()

protected:
	void SpawnChildCarriers();

	void ApplyEffects(const TArray<AActor *>& InTargets);
	
protected:
	UPROPERTY(EditDefaultsOnly, Instanced, NoClear, Category="Carrier Children")
	TArray<ABuffDebuffCarrierBase *> SpawningCarriers;

	UPROPERTY(EditDefaultsOnly, Instanced, NoClear, Category="Carrier Children")
	TArray<UBuffDebuffEffectBase *> SpawningEffects;
};
