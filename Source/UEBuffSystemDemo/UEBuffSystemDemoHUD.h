// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "UEBuffSystemDemoHUD.generated.h"

UCLASS()
class AUEBuffSystemDemoHUD : public AHUD
{
	GENERATED_BODY()

public:
	AUEBuffSystemDemoHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

