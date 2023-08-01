// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Carriers/BuffDebuffCarrierBase.h"
#include "BuffDebuffPickupBase.generated.h"

class USphereComponent;

UCLASS()
class UEBUFFSYSTEM_API ABuffDebuffPickupBase : public ABuffDebuffCarrierBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuffDebuffPickupBase();
	
	/** A virtual method called on "BeginOverlap". To change the basic logic, you need to override it. */
	UFUNCTION()
	virtual void OnActivateCollisionComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
protected:	
	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;
};
