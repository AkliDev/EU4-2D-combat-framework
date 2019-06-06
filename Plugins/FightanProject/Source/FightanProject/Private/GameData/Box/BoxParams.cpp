// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxParams.h"

FBoxParams::FBoxParams()
{
	Position = FVector(32, 0, 32);
	Extent = FVector(32, 0, 32);
	LifeTime = 0.1f;
}

FHitBoxParams::FHitBoxParams()
{
	HitRumbleIntensity = 5;
	HitRumbleSpeed = 80;
	HitStop = FVector2D(0.15f, 0.15f);
	GroundKnockBackVelocity = FVector(200, 0, 0);
}