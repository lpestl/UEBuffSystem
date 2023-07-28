// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffDebuffEffectBase.h"
#include "PoisonEffect.generated.h"

UCLASS()
class UEBUFFSYSTEM_API APoisonEffect : public ABuffDebuffEffectBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APoisonEffect();

	virtual void Init(const FBuffDataTableRow& InBuffData) override;

	virtual void ApplyEffect_Implementation() override;
	
	virtual void Tick(float DeltaTime) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor *> OverlappingActors;
};
