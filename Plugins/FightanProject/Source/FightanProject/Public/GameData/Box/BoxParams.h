// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BoxParams.generated.h"

/**
 * 
 */
UENUM(Blueprintable, Meta = (Bitflags))
enum class BoxType : uint8
{
	HIT_BOX,
	HURT_BOX
};

USTRUCT()
struct FIGHTANPROJECT_API FBoxParams
{
	GENERATED_BODY()

public:

	FBoxParams();
	FBoxParams(FVector position, FVector extent, float lifeTime);

	UPROPERTY(EditAnywhere)
		FVector Position;
	UPROPERTY(EditAnywhere)
		FVector Extent;
	UPROPERTY(EditAnywhere)
		float LifeTime;
};

UENUM(Blueprintable, Meta = (Bitflags))
enum class AttackType : uint8
{
	Normal
};

USTRUCT()
struct FIGHTANPROJECT_API FHitBoxParams
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		AttackType Type;
	UPROPERTY(EditAnywhere)
		FVector2D HitStop;
};
