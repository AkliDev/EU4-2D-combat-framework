// Fill out your copyright notice in the Description page of Project Settings.


#include "GameData/Box/BoxInstruction.h"

FBoxParams::FBoxParams()
	:Position(FVector::ZeroVector), Extent(FVector::ZeroVector), LifeTime(0.0f)
{
}

FBoxParams::FBoxParams(FVector position, FVector extent, float lifeTime)
	: Position(position), Extent(extent), LifeTime(lifeTime)
{
}