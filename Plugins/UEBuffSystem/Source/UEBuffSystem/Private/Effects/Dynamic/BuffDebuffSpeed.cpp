// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/Dynamic/BuffDebuffSpeed.h"

#include "Interfaces/IBuffReceiver.h"


void UBuffDebuffSpeed::Impact()
{
	Super::Impact();
	
	if (auto SpeedEffectParams = Cast<UBuffDebuffSpeedParams>(EffectParams))
	{
		if (GetOwner() != nullptr)
		{
			if (GetOwner()->GetClass()->ImplementsInterface(UBuffReceiver::StaticClass()))
			{
				IBuffReceiver::Execute_AddSpeed(GetOwner(), SpeedEffectParams->AddSpeed);
				AmountChangeSpeed += SpeedEffectParams->AddSpeed;
			}
		}
	}
}

void UBuffDebuffSpeed::CancelImpact()
{
	if (GetOwner() != nullptr)
	{
		if (GetOwner()->GetClass()->ImplementsInterface(UBuffReceiver::StaticClass()))
		{
			IBuffReceiver::Execute_AddSpeed(GetOwner(), -AmountChangeSpeed);
		}
	}
	
	Super::CancelImpact();
}
