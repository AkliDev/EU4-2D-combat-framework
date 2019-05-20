// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BoxFrameData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, hidecategories = (Object))
class FIGHTANPROJECT_API UBoxFrameData : public UDataAsset
{
	GENERATED_BODY()
public:
	/** Holds the stored text. */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "BoxFrameData")
		FText Text;
	
};
