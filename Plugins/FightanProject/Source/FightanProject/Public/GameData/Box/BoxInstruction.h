// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Classes/Engine/DataTable.h"
#include "GameData/Box/BoxParams.h"
#include "BoxInstruction.generated.h"

/**
 *
 */

USTRUCT()
struct FIGHTANPROJECT_API FBoxData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		BoxType Type;

	UPROPERTY(EditAnywhere)
		FBoxParams BoxParams;

	UPROPERTY(EditAnywhere)
		FHitBoxParams HitParams;

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
