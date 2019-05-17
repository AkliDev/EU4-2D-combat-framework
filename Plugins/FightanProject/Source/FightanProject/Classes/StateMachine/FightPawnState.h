// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Paper2D/Classes/PaperFlipbookComponent.h"
#include "StateBehaviourData.h"
#include "StateChangeComponent.h"
#include "StateMachineResults.h"
#include "Input/InputBuffer/InputBufferComponent.h"
#include "FightPawnState.generated.h"

/**
 *
 */

UCLASS(ClassGroup = StateMachine, Category = "StateMachine", BlueprintType, Blueprintable)
class FIGHTANPROJECT_API UFightPawnState : public UDataAsset
{
	GENERATED_BODY()

public:
	UFightPawnState();

	UPROPERTY(EditAnywhere)
		FName StateName;

	// Instructions for behavior
	UPROPERTY(EditAnywhere)
		UStateBehaviourData* StateBehaviour;
	//TODO: Collision date
	
	// The animation that is associated with this state
	UPROPERTY(EditAnywhere)
		UPaperFlipbook* Animation;	

	// Component that holds links for this state
	UPROPERTY(EditAnywhere)
		UStateChangeComponent* StateChangeComponent;

	//Should the animation of this state loop?
	UPROPERTY(EditAnywhere)
		uint32 bLoops : 1;

	// Clears input buffer when entering this state.
	UPROPERTY(EditAnywhere)
		uint32 bClearInputbufferOnEntry : 1;

	// Clears input buffer when exiting this state.
	UPROPERTY(EditAnywhere)
		uint32 bClearInputbufferOnExit : 1;

public:
	// Tries out all links in the links array with the given input buffer
	UFUNCTION()
		FStateMachineResult TryLinks(AFightPawn* refObject, const UInputBufferComponent* InputBuffer);
};
