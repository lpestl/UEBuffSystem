// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effects/BuffDebuffEffectBase.h"
#include "BuffDebuffHealth.generated.h"

UCLASS(BlueprintType, EditInlineNew)
class UEBUFFSYSTEM_API UBuffDebuffHealthParams : public UBuffDebuffEffectParamsBase
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health Effect Settings")
	float AddHealth = -100.f;	
};

/*
 *
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEBUFFSYSTEM_API UBuffDebuffHealth : public UBuffDebuffEffectBase
{
	GENERATED_BODY()

public:
	virtual void Impact() override;
	virtual void CancelImpact() override;

private:
	UPROPERTY()
	float AmountChangeHealth = 0.f;
};
