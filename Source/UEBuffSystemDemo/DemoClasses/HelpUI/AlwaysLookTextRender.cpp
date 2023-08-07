// Fill out your copyright notice in the Description page of Project Settings.


#include "AlwaysLookTextRender.h"

UAlwaysLookTextRender::UAlwaysLookTextRender()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called every frame
void UAlwaysLookTextRender::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (APlayerController* FirstPlayerController = GetWorld()->GetFirstPlayerController())
	{
		FRotator PCRotation = FirstPlayerController->K2_GetActorRotation();
		SetWorldRotation(PCRotation);

		AddLocalRotation(FRotator(0.f, -180.f, 0.f));
	}
}

