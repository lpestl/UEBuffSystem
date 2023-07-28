// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffDataTableRow.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "BuffDebuffCarrierBase.generated.h"

UCLASS()
class UEBUFFSYSTEM_API ABuffDebuffCarrierBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuffDebuffCarrierBase();

	virtual void Init(const FBuffDataTableRow& InData);
	
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	
protected:
	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	UPROPERTY()
	FBuffDataTableRow BuffData;
};
