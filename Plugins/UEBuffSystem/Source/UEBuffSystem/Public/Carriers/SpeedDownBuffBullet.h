// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BuffDebuffCarrierBase.h"
#include "SpeedDownBuffBullet.generated.h"

class UProjectileMovementComponent;

UCLASS()
class UEBUFFSYSTEM_API ASpeedDownBuffBullet : public ABuffDebuffCarrierBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpeedDownBuffBullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** called when projectile hits something */
	virtual void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

private:
	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

};
