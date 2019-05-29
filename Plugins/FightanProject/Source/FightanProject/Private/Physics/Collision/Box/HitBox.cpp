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