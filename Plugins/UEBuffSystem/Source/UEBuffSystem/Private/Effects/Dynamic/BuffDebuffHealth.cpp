// Fill out your copyright notice in the Description page of Project Settings.


#include "Effects/Dynamic/BuffDebuffHealth.h"

#include "Interfaces/IBuffReceiver.h"

void UBuffDebuffHealth::Impact()
{
	Super::Impact();

	if (auto HealthEffectParams = Cast<UBuffDebuffHealthParams>(EffectParams))
	{
		if (GetOwner() != nullptr)
		{
			if (GetOwner()->GetClass()->ImplementsInterface(UBuffReceiver::StaticClass()))
			{
				IBuffReceiver::Execute_AddHealth(GetOwner(), HealthEffectParams->AddHealth);
				AmountChangeHealth += HealthEffectParams->AddHealth;
			}
		}
	}
}

void UBuffDebuffHealth::CancelImpact()
{
	if (GetOwner() != nullptr)
	{
		if (GetOwner()->GetClass()->ImplementsInterface(UBuffReceiver::StaticClass()))
		{
			IBuffReceiver::Execute_AddHealth(GetOwner(), -AmountChangeHealth);
		}
	}
	
	Super::CancelImpact();
}


