// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuffDebuffCarrierBase.generated.h"

class UBuffDebuffEffectBase;
class ABuffDebuffCarrierBase;
class UBuffDebuffEffectParamsBase;

/*
 * Base Carrier Params class
 */
UCLASS(BlueprintType, Abstract)
class UEBUFFSYSTEM_API UBuffDebuffCarrierParamsBase : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning class")
	TSubclassOf<ABuffDebuffCarrierBase> CarrierClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="Next generation")
	TArray<UBuffDebuffCarrierParamsBase *> ChildCarriers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="Next generation")
	TArray<UBuffDebuffEffectParamsBase *> ChildEffects;
};

/*
 * Base class for buff carrier
 */
UCLASS(BlueprintType, Abstract)
class UEBUFFSYSTEM_API ABuffDebuffCarrierBase : public AActor
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void Init(UBuffDebuffCarrierParamsBase *InCarrierParams);

	UFUNCTION(BlueprintCallable)
	void SpawnChildCarriers();
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffects(const TArray<AActor *>& InTargets);
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="Carrier chain")
	UBuffDebuffCarrierParamsBase *CarrierParams = nullptr;
};
