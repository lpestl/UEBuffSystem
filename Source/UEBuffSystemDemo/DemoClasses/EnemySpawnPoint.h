// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnPoint.generated.h"

class AEnemy;

UCLASS()
class UEBUFFSYSTEMDEMO_API AEnemySpawnPoint : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemySpawnPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	bool SpawnEnemy();
	
	UFUNCTION()
	void OnCurrentEnemyDestroyed(AActor* DestroyedActor);	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	AEnemy *CurrentEnemy;

	UPROPERTY(meta=(AllowPrivateAccess="true"), EditAnywhere, BlueprintReadWrite, Category=Classes)
	UClass *EnemyClass;
};
