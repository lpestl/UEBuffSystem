// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffDebuffEffectBase.generated.h"

class UBuffDebuffCarrierParamsBase;
class UBuffDebuffEffectBase;
class USphereComponent;

/*
 *
 */
UCLASS(BlueprintType, Abstract)
class UEBUFFSYSTEM_API UBuffDebuffEffectParamsBase : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawning class")
	TSubclassOf<UBuffDebuffEffectBase> EffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effect")
	FName Name;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effect Settings")
	bool bIsCancelableEffect = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effect Settings")
	float LifeTime = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effect Settings")
	bool bIsCycle = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effect Settings")
	float CycleTime = 0.f;	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="Next generation")
	TArray<UBuffDebuffCarrierParamsBase *> ChildCarriers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category="Next generation")
	TArray<UBuffDebuffEffectParamsBase *> ChildEffects;
};

/*
 *
 */
UCLASS(Abstract)
class UEBUFFSYSTEM_API UBuffDebuffEffectBase : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual void Init(UBuffDebuffEffectParamsBase *InParams);

	virtual void Impact() {};
	virtual void CancelImpact() {};
	
	void DestroyEffect();

	UFUNCTION(BlueprintCallable)
	void SpawnChildCarriers();
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffects(const TArray<AActor *>& InTargets);
	
	UFUNCTION(BlueprintCallable)
	virtual FName GetBuffEffectName();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effect params")
	UBuffDebuffEffectParamsBase *EffectParams;
	
	UPROPERTY()
	FTimerHandle EffectCycleTimerHandle;

	UPROPERTY()
	FTimerHandle LifeTimerHandle;
};
