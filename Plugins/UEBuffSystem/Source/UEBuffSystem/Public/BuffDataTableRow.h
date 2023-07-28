// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "BuffDataTableRow.generated.h"

class ABuffDebuffCarrierBase;
class ABuffDebuffEffectBase;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FBuffDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Buff data")
	TSoftClassPtr<ABuffDebuffCarrierBase> CarrierClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Buff data")
	TSoftClassPtr<ABuffDebuffEffectBase> EffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Buff data")
	float LifeTimeEffect;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Buff data")
	float ImpactCycleTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Buff data")
	float EffectRadius;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Buff data")
	float HealthImpactValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Buff data")
	float SpeedImpactValue;
};

