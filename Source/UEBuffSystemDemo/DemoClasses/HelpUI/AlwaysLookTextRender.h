// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextRenderComponent.h"
#include "AlwaysLookTextRender.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class UEBUFFSYSTEMDEMO_API UAlwaysLookTextRender : public UTextRenderComponent
{
	GENERATED_BODY()
	
public:
	UAlwaysLookTextRender();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
