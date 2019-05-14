// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StateLink.h"
#include "StateChangeComponent.generated.h"

/**
 *
 */
UCLASS()
class FIGHTANPROJECT_API UStateChangeComponent : public UDataAsset
{
	GENERATED_BODY()
public:

	//Links from this state to other states
	UPROPERTY(EditAnywhere)
		TArray<UStateLink*> Links;

	// State to go when this state has finished;
	UPROPERTY(EditAnywhere, category = "Event State Changes")
		UFightPawnState* OnFinishState;
};
