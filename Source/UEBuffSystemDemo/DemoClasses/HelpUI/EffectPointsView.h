// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AlwaysLookTextRender.h"
#include "GameFramework/Actor.h"
#include "EffectPointsView.generated.h"

UCLASS()
class UEBUFFSYSTEMDEMO_API AEffectPointsView : public AActor
{
	GENERATED_BODY()

public:
	AEffectPointsView();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void SetText(const FString& InString);
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAlwaysLookTextRender* EffectPointsText;
};
