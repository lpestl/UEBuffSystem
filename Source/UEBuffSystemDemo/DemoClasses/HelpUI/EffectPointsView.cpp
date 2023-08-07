// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectPointsView.h"

#include "AlwaysLookTextRender.h"


AEffectPointsView::AEffectPointsView()
{
	PrimaryActorTick.bCanEverTick = true;
	
	InitialLifeSpan = 3.f;
	EffectPointsText = CreateDefaultSubobject<UAlwaysLookTextRender>(TEXT("EffectPoints"));
	
	RootComponent = EffectPointsText;
}

// Called when the game starts or when spawned
void AEffectPointsView::BeginPlay()
{
	Super::BeginPlay();	
}

void AEffectPointsView::SetText(const FString& InString)
{
	EffectPointsText->SetText(InString);
}

// Called every frame
void AEffectPointsView::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorLocalOffset(FVector(0.f, 0.f, 2.5f));
}

