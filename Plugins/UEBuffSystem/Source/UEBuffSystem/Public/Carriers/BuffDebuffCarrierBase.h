// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffDataTableRow.h"
#include "GameFramework/Actor.h"
#include "BuffDebuffCarrierBase.generated.h"

/*
 * Base class for buff carrier
 */
UCLASS()
class UEBUFFSYSTEM_API ABuffDebuffCarrierBase : public AActor
{
	GENERATED_BODY()

public:
	/** For initialization, you need to transfer only data about the effect from the DataTable */
	virtual void Init(const FBuffDataTableRow& InData)
	{
		BuffData = InData;
	}
	
protected:
	/** Buff Carrier Base class will only store effect data */
	UPROPERTY()
	FBuffDataTableRow BuffData;
};
