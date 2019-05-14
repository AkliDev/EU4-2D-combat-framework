// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Box/FGCollisionBoxBase.h"
#include "CollisionUtility.generated.h"

/**
 * 
 */
USTRUCT()
struct FIGHTANPROJECT_API FOverLapData
{
	GENERATED_BODY()

public:
	FOverLapData();
	FOverLapData(float xOverlap, float zOverLap, FVector mtv);

	float XOverLap;
	float ZOverLap;
	FVector MTV;

};

UCLASS()
class FIGHTANPROJECT_API UCollisionUtility : public UObject
{
	GENERATED_BODY()

public:

	static bool AreBoxesIntersecting(UFGCollisionBoxBase* a, UFGCollisionBoxBase* b);
	static bool AreBoxesIntersecting(UCastBox* a, UCastBox* b);
	static bool AreBoxesIntersecting(UCastBox* a, UFGCollisionBoxBase* b);

	static FOverLapData GetBoxOverlap(UFGCollisionBoxBase* a, UFGCollisionBoxBase* b);
	static FOverLapData GetBoxOverlap(UCastBox* a, UCastBox* b);
	static FOverLapData GetBoxOverlap(UCastBox* a, UFGCollisionBoxBase* b);
	
};
