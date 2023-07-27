// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Enemy.h"
#include "EnemySpawnPoint.generated.h"

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
	FEnemyCharacteristics CreateRandomCharacteristics();
	
	UFUNCTION()
	void OnCurrentEnemyDestroyed(AActor* DestroyedActor);	
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	AEnemy *CurrentEnemy;

	UPROPERTY(meta=(AllowPrivateAccess="true"), EditAnywhere, BlueprintReadWrite, Category=Classes)
	UClass *EnemyClass;

	UPROPERTY(meta=(AllowPrivateAccess="true"), EditAnywhere, BlueprintReadWrite, Category=Classes)
	TArray<float> AllowedStartSpeedList;

	UPROPERTY(meta=(AllowPrivateAccess="true"), EditAnywhere, BlueprintReadWrite, Category=Classes)
	TArray<FLinearColor> AllowedColors;

	UPROPERTY(meta=(AllowPrivateAccess="true"), EditAnywhere, BlueprintReadWrite, Category=Classes)
	TArray<float> AllowedHealthsList;	
};
