// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "FightanProjectGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTANPROJECT_API UFightanProjectGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFightanProjectGameInstance();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FG System Settings")
		float MotionLifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FG System Settings")
		float ValidTimeBetweenInputsInSequence;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "FG System Settings")
		float ValidHoldTimePerInputInSequence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Physics Settings")
		float BaseGravity;
	
};