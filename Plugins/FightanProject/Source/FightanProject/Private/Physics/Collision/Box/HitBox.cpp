// Fill out your copyright notice in the Description page of Project Settings.


#include "Physics/Collision/Box/HitBox.h"

UHitBox::UHitBox()
{
	ShapeColor = FColor::Red;
}

void UHitBox::Deactivate()
{
	Super::Deactivate();
	HitPawns.Empty();
}

void UHitBox::Init(FBoxParams& params, FHitBoxParams& hitParams)
{
	SetRelativeLocation(params.Position);
	SetBoxExtent(params.Extent);
	LifeTime = params.LifeTime;

	HitParams = hitParams;

	bInUse = true;
	SetHiddenInGame(false);
}
