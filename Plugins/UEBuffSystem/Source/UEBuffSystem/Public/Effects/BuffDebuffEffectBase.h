// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Carriers/BuffDebuffCarrierBase.h"
#include "GameFramework/Actor.h"
#include "BuffDebuffEffectBase.generated.h"

UCLASS()
class UEBUFFSYSTEM_API ABuffDebuffEffectBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuffDebuffEffectBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;	

	UFUNCTION(BlueprintImplementableEvent)
	void ApplyEffect();
	virtual void ApplyEffect_Implementation();

	UFUNCTION(BlueprintImplementableEvent)
	void CancelEffect();
	virtual void CancelEffect_Implementation();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void Init(const FBuffDataTableRow& InBuffData);
	
	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	
protected:
	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBuffDataTableRow BuffData;
	
	FTimerHandle CycleTimerHandle;
};
