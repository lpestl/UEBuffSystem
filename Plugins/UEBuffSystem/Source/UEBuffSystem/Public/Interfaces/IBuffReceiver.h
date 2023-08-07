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
	/** Called for change health */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddHealth(float AddHealthValue);
	virtual void AddHealth_Implementation(float AddHealthValue) {};
	
	/** Called for change speed */
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AddSpeed(float AddSpeedValue);
	virtual void AddSpeed_Implementation(float AddSpeedValue) {};
};
