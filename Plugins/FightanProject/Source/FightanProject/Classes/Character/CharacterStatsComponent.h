// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CharacterStatsComponent.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTANPROJECT_API UCharacterStatsComponent : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		float Weight;	

	UPROPERTY(EditAnywhere)
		float FallSpeed;
};
