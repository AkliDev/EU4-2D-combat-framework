// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMachine/FightPawnState.h"

UFightPawnState::UFightPawnState()
{
	bLoops = true;
}

/// <summary>Itterates through links of this state and passes value to these links to be checked</summary>
/// <param name="sel">Reference to the subject pawn and Input buffer conponent preferably of the same pawn </param>  
/// <returns>FStateMachineResult</returns>  
FStateMachineResult UFightPawnState::TryLinks(AFightPawn* refObject, const UInputBufferComponent* InputBuffer)
{
	FStateMachineResult result;

	if (StateChangeComponent == nullptr)
		return result;

	for (UStateLink* link : StateChangeComponent->Links)
	{
		if (link != nullptr)
			result = link->TryLink(refObject, InputBuffer);
		if (result.DestinationState != nullptr)
			break;
	}

	return result;
}