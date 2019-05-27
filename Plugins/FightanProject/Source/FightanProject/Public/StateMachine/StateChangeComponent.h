// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StateLink.h"
#include "StateChangeComponent.generated.h"

/**
 *
 */

USTRUCT()
struct FIGHTANPROJECT_API FOnFinishState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		UFightPawnState* NextState;

	UPROPERTY(EditAnywhere)
		float Time;
};
UCLASS()
class FIGHTANPROJECT_API UStateChangeComponent : public UDataAsset
{
	GENERATED_BODY()
public:

	//Links from this state to other states
	UPROPERTY(EditAnywhere)
		TArray<UStateLink*> Links;

	// State to go when this state has finished;
	UPROPERTY(EditAnywhere)
		FOnFinishState OnFinishState;
};
