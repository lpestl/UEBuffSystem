// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	/** For initialization, you need to transfer only class about the effect */
	virtual void Init(UClass* InEffectClass)
	{
		EffectClass = InEffectClass;
	}
	
protected:
	/** Buff Carrier Base class will only store effect class */
	UPROPERTY()
	UClass* EffectClass;
};
