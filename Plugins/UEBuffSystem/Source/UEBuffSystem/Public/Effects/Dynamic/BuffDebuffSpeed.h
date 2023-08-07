// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Effects/BuffDebuffEffectBase.h"
#include "BuffDebuffSpeed.generated.h"

UCLASS(BlueprintType, EditInlineNew)
class UEBUFFSYSTEM_API UBuffDebuffSpeedParams : public UBuffDebuffEffectParamsBase
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Speed Effect Settings")
	float AddSpeed = -200.f;	
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEBUFFSYSTEM_API UBuffDebuffSpeed : public UBuffDebuffEffectBase
{
	GENERATED_BODY()
	
public:
	virtual void Impact() override;
	virtual void CancelImpact() override;

private:
	UPROPERTY()
	float AmountChangeSpeed = 0.f;
};
