// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffDebuffEffectBase.h"
#include "SpeedDownBuffEffect.generated.h"

UCLASS()
class UEBUFFSYSTEM_API ASpeedDownBuffEffect : public ABuffDebuffEffectBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpeedDownBuffEffect();

	virtual void Init(const FBuffDataTableRow& InBuffData) override;

	virtual void ApplyEffect_Implementation() override;
	virtual void CancelEffect_Implementation() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
protected:
	UPROPERTY()
	TArray<AActor *> OverlappingActors;
};
