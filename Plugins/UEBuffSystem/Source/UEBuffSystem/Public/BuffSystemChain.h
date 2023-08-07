// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Carriers/BuffDebuffCarrierBase.h"
#include "Engine/DataAsset.h"
#include "BuffSystemChain.generated.h"

USTRUCT(BlueprintType)
struct FCarrierParams
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UBuffDebuffCarrierParamsBase *Params;
};

/**
 * 
 */
UCLASS(BlueprintType)
class UEBUFFSYSTEM_API UBuffSystemChain : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCarrierParams> BuffCarriers;
};
