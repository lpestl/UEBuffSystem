﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Carriers/BuffDebuffCarrierBase.h"
#include "BuffDebuffProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS(BlueprintType, EditInlineNew)
class UEBUFFSYSTEM_API UBuffDebuffProjectileParams : public UBuffDebuffCarrierParamsBase
{
	GENERATED_BODY()

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile Settings")
	float Speed = 3000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile Settings")
	float LifeTime = 3.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile Settings")
	bool bIsActivateByEndOfLife = false;
};

/*
 *
 */
UCLASS(BlueprintType)
class UEBUFFSYSTEM_API ABuffDebuffProjectileBase : public ABuffDebuffCarrierBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuffDebuffProjectileBase();

	virtual void Init(UBuffDebuffCarrierParamsBase* InCarrierParams) override;
	
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
	
	/** A virtual method called on "hit". To change the basic logic, you need to override it. */
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Projectile movement component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

private:
	UPROPERTY()
	bool bNeedActivateByEndPlay = false;
};
