// Fill out your copyright notice in the Description page of Project Settings.


#include "Physics/Collision/CollisionUtility.h"
#include "DrawDebugHelpers.h"
#include "Classes/Kismet/KismetMathLibrary.h"

FOverLapData::FOverLapData() {}
FOverLapData::FOverLapData(float xOverlap, float zOverLap, FVector mtv)
	:XOverLap(xOverlap), ZOverLap(zOverLap), MTV(mtv) {}

bool UCollisionUtility::AreBoxesIntersecting(UFGCollisionBoxBase* a, UFGCollisionBoxBase* b)
{
	return (FMath::Abs(a->GetCenterOfBox().X - b->GetCenterOfBox().X) < a->GetScaledBoxExtent().X + b->GetScaledBoxExtent().X &&
		FMath::Abs(a->GetCenterOfBox().Z - b->GetCenterOfBox().Z) < a->GetScaledBoxExtent().Z + b->GetScaledBoxExtent().Z);
}

bool UCollisionUtility::AreBoxesIntersecting(UCastBox* a, UCastBox* b)
{
	return (FMath::Abs(a->GetPosition().X - b->GetPosition().X) < a->GetExtent().X + b->GetExtent().X &&
		FMath::Abs(a->GetPosition().Z - b->GetPosition().Z) < a->GetExtent().Z + b->GetExtent().Z);
}

bool UCollisionUtility::AreBoxesIntersecting(UCastBox* a, UFGCollisionBoxBase* b)
{
	return (FMath::Abs(a->GetPosition().X - b->GetCenterOfBox().X) < a->GetExtent().X + b->GetScaledBoxExtent().X &&
		FMath::Abs(a->GetPosition().Z - b->GetCenterOfBox().Z) < a->GetExtent().Z + b->GetScaledBoxExtent().Z);
}

FOverLapData UCollisionUtility::GetBoxOverlap(UFGCollisionBoxBase* a, UFGCollisionBoxBase* b)
{
	float xOverlap;
	float zOverlap;
	FVector mtv;

	xOverlap = a->GetScaledBoxExtent().X + b->GetScaledBoxExtent().X - FMath::Abs(a->GetCenterOfBox().X - b->GetCenterOfBox().X);
	zOverlap = a->GetScaledBoxExtent().Z + b->GetScaledBoxExtent().Z - FMath::Abs(a->GetCenterOfBox().Z - b->GetCenterOfBox().Z);

	if (a->GetCenterOfBox().X < b->GetCenterOfBox().X)
		xOverlap = -xOverlap;

	if (a->GetCenterOfBox().Z < b->GetCenterOfBox().Z)
		zOverlap = -zOverlap;

	if (FMath::Abs(xOverlap) < FMath::Abs(zOverlap))
		mtv = FVector(xOverlap, 0, 0);
	else
		mtv = FVector(0, 0, zOverlap);

	return FOverLapData(xOverlap, zOverlap, mtv);
}

FOverLapData UCollisionUtility::GetBoxOverlap(UCastBox* a, UCastBox* b)
{
	float xOverlap;
	float zOverlap;
	FVector mtv;

	xOverlap = a->GetExtent().X + b->GetExtent().X - FMath::Abs(a->GetPosition().X - b->GetPosition().X);
	zOverlap = a->GetExtent().Z + b->GetExtent().Z - FMath::Abs(a->GetPosition().Z - b->GetPosition().Z);

	if (a->GetPosition().X < b->GetPosition().X)
		xOverlap = -xOverlap;

	if (a->GetPosition().Z < b->GetPosition().Z)
		zOverlap = -zOverlap;

	if (FMath::Abs(xOverlap) < FMath::Abs(zOverlap))
		mtv = FVector(xOverlap, 0, 0);
	else
		mtv = FVector(0, 0, zOverlap);

	return FOverLapData(xOverlap, zOverlap, mtv);
}

FOverLapData UCollisionUtility::GetBoxOverlap(UCastBox* a, UFGCollisionBoxBase* b)
{
	float xOverlap;
	float zOverlap;
	FVector mtv;

	xOverlap = a->GetExtent().X + b->GetScaledBoxExtent().X - FMath::Abs(a->GetPosition().X - b->GetCenterOfBox().X);
	zOverlap = a->GetExtent().Z + b->GetScaledBoxExtent().Z - FMath::Abs(a->GetPosition().Z - b->GetCenterOfBox().Z);

	if (a->GetPosition().X < b->GetCenterOfBox().X)
		xOverlap = -xOverlap;

	if (a->GetPosition().Z < b->GetCenterOfBox().Z)
		zOverlap = -zOverlap;

	if (FMath::Abs(xOverlap) < FMath::Abs(zOverlap))
		mtv = FVector(xOverlap, 0, 0);
	else
		mtv = FVector(0, 0, zOverlap);

	return FOverLapData(xOverlap, zOverlap, mtv);
}
