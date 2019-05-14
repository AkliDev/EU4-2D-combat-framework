// Fill out your copyright notice in the Description page of Project Settings.

#include "StateMachine/StateMachineResults.h"

FInputValidationResult::FInputValidationResult()
{
	SequenceResultType = ESequenceCompletionType::INVALID_SEQUENCE;
	bMotionLock = false;
}

bool FInputValidationResult::IsInputValid()
{
	if (SequenceResultType != ESequenceCompletionType::INVALID_SEQUENCE && IsCurrentInputValid == true)
		return true;
	else
		return false;
}

FStateMachineResult::FStateMachineResult()
{
	DestinationState = nullptr;
	bClearBuffer = false;
}