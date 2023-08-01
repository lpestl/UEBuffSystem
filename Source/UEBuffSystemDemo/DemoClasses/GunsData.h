// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffDataTableRow.h"
#include "UEBuffSystemDemo/UEBuffSystemDemoCharacter.h"
#include "GunsData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FGunsDataRow : public FBuffDataTableRow
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Buff data")
	EGunType GunType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Buff data")
	float HealthImpactValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Buff data")
	float SpeedImpactValue;
};
