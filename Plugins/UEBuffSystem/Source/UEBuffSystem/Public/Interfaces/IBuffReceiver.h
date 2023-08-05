// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IBuffReceiver.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UBuffReceiver : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class UEBUFFSYSTEM_API IBuffReceiver
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void BuffImpact(UClass* InEffectClass);
	virtual void BuffImpact_Implementation(UClass* InEffectClass) {};
};
