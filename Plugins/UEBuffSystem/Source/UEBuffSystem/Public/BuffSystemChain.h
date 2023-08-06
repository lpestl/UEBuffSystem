// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Carriers/BuffDebuffCarrierBase.h"
#include "Engine/DataAsset.h"
#include "BuffSystemChain.generated.h"

/**
 * 
 */
UCLASS()
class UEBUFFSYSTEM_API UBuffSystemChain : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(Instanced, EditDefaultsOnly, NoClear)
	TArray<ABuffDebuffCarrierBase *> BuffCarriers;
};
