// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffDebuffEffectBase.generated.h"

class UBuffDebuffCarrierParamsBase;
class UBuffDebuffEffectBase;
class USphereComponent;

/*
 *
 */
UCLASS(BlueprintType, Abstract)
class UEBUFFSYSTEM_API UBuffDebuffEffectParamsBase : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning class")
	TSubclassOf<UBuffDebuffEffectBase> EffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effect")
	FName Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="Next generation")
	TArray<UBuffDebuffCarrierParamsBase *> ChildCarriers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="Next generation")
	TArray<UBuffDebuffEffectParamsBase *> ChildEffects;
};

/*
 *
 */
UCLASS(Abstract)
class UEBUFFSYSTEM_API UBuffDebuffEffectBase : public UActorComponent
{
	GENERATED_BODY()

public:
	UBuffDebuffEffectBase();

	virtual FName GetBuffEffectName();
};
