// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Classes/Engine/DataTable.h"
#include "BoxInstruction.generated.h"

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

USTRUCT()
struct FIGHTANPROJECT_API FBoxData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		BoxType Type;

	UPROPERTY(EditAnywhere)
		FBoxParams Params;

};

USTRUCT()
struct FIGHTANPROJECT_API FBoxInstructionRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float Time;

	UPROPERTY(EditAnywhere)
		TArray<FBoxData> FrameBoxes;
};
