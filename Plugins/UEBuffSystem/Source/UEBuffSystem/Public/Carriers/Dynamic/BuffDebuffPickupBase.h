// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Carriers/BuffDebuffCarrierBase.h"
#include "BuffDebuffPickupBase.generated.h"

class USphereComponent;

UCLASS(BlueprintType, EditInlineNew)
class UEBUFFSYSTEM_API UBuffDebuffPickupParams : public UBuffDebuffCarrierParamsBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup Settings")
	bool bIsDestroyAfterOverlap = true;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Pickup Settings")
	float LifeTime = 0.f;
};

UCLASS(BlueprintType)
class UEBUFFSYSTEM_API ABuffDebuffPickupBase : public ABuffDebuffCarrierBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuffDebuffPickupBase();

	virtual void Init(UBuffDebuffCarrierParamsBase* InCarrierParams) override;
	
	/** A virtual method called on "BeginOverlap". To change the basic logic, you need to override it. */
	UFUNCTION()
	virtual void OnActivateCollisionComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY()
	TArray<AActor *> AffectedActors;
};
