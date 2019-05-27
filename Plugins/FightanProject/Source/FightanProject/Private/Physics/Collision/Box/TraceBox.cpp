// Fill out your copyright notice in the Description page of Project Settings.

#include "Physics/Collision/Box/TraceBox.h"

UTraceBox::UTraceBox()
{
	ShapeColor = FColor(220, 220, 220);
	bInUse = false;
	SetHiddenInGame(true);
}

void UTraceBox::Init(FBoxParams& params)
{
	SetRelativeLocation(params.Position);
	SetBoxExtent(params.Extent);
	LifeTime = params.LifeTime;

	bInUse = true;
	SetHiddenInGame(false);
}

void UTraceBox::Deactivate()
{
	bInUse = false;
	SetHiddenInGame(true);
}