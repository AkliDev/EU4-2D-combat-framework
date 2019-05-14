// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Character/FightPawn.h"
#include "Input/Condition/InputCondition.h"
#include "StateMachineResults.h"
#include "Input/InputBuffer/InputBufferComponent.h"
#include "StateLink.generated.h"

//Forward declaration to prevent circular dependency 
class UFightPawnState;

/**
 *
 */
UCLASS()
class FIGHTANPROJECT_API UStateLink : public UDataAsset
{
	GENERATED_BODY()

protected:
	//The destination state of this link
	UPROPERTY(EditAnywhere)
		UFightPawnState* LinkedState;

	//Input(s) required to take this link
	UPROPERTY(EditAnywhere)
		UInputCondition* InputCondition;

	//TODO? Add event condition component

	//The time window when his link is valid
	UPROPERTY(EditAnywhere)
		TArray<FVector2D> CancelWindows;

	//True if you want to clear the input buffer if this link is taken
	UPROPERTY(EditAnywhere)
		uint32 bClearInputbuffer : 1;

public:
	//Tries out the link with a given input buffer
	UFUNCTION()
		FStateMachineResult TryLink(AFightPawn* refObject, const UInputBufferComponent* InputBuffer);
};