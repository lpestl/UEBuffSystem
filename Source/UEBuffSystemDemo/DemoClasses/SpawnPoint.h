// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnPoint.generated.h"

UCLASS()
class UEBUFFSYSTEMDEMO_API ASpawnPoint : public AActor
{
	GENERATED_BODY()

public:	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION()
	virtual void SpawnActor();
	
	UFUNCTION()
	void OnCurrentActorDestroyed(AActor* DestroyedActor);

	void Unsubscribe();	
protected:
	UPROPERTY(meta=(AllowPrivateAccess="true"), EditAnywhere, BlueprintReadWrite, Category=Classes)
	UClass *SpawnActorClass { nullptr };

	UPROPERTY(meta=(AllowPrivateAccess="true"), EditAnywhere, BlueprintReadWrite, Category=Classes)
	float RespawnTime { 0.f };

private:
	UPROPERTY()
	AActor *CurrentActor { nullptr };

	UPROPERTY()
	FTimerHandle RespawnTimerHandle;
};
