// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffDebuffEffectBase.generated.h"

class USphereComponent;

UCLASS()
class UEBUFFSYSTEM_API UBuffDebuffEffectBase : public UActorComponent
{
	GENERATED_BODY()

public:
	UBuffDebuffEffectBase();

	virtual FName GetBuffEffectName();
};
