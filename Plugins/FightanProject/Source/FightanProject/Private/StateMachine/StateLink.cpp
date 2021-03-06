// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMachine/StateLink.h"

/// <summary>Itterates through input condition for this link and passes value to these conditions to be checked</summary>
/// <param name="sel">Reference to the subject pawn and Input buffer conponent preferably of the same pawn </param>  
/// <returns>FStateMachineResult</returns>  
FStateMachineResult UStateLink::TryLink(AFightPawn* refObject, const UInputBufferComponent* InputBuffer)
{
	FStateMachineResult result;

	for (int i = 0; i < CancelWindows.Num(); i++)
	{
		if (refObject->GetStateTimer() > CancelWindows[i].X && refObject->GetStateTimer() < CancelWindows[i].Y)		
			break;
	
		if (i >= CancelWindows.Num() - 1)
			return result;
	}

	if (InputCondition != nullptr)
	{
		result.InputValidationResult = InputCondition->ValidateInput(refObject, InputBuffer);
		if (result.InputValidationResult.IsInputValid())
		{
			if (LinkedState != nullptr)
			{
				result.bClearBuffer = bClearInputbuffer;
				result.DestinationState = LinkedState;
			}
		}
	}
	return result;
}