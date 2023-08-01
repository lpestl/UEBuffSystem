// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Carriers/BuffDebuffCarrierBase.h"
#include "BuffDebuffProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class UEBUFFSYSTEM_API ABuffDebuffProjectileBase : public ABuffDebuffCarrierBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABuffDebuffProjectileBase();

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }

	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
	
	/** A virtual method called on "hit". To change the basic logic, you need to override it. */
	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:	
	/** Sphere collision component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Projectile)
	USphereComponent* CollisionComp;
	
	/** Projectile movement component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

};
