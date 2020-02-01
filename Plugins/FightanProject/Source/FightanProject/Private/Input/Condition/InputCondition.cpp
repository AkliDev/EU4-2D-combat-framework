// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/Condition/InputCondition.h"
#include "Input/InputUtility.h"

UTapSequence::UTapSequence()
{
	Type = SequneceType::TAP;
}

/// <summary>Passer function that calls checks for input sequences and current input</summary>
/// <param name="sel">Pointer to pawn  and Pointer to InputBufferItem preferrably the one owned by the given pawn </param>  
/// <returns>FInputValidationResult, Returns the result of input parsing</returns>  
FInputValidationResult UInputCondition::ValidateInput(AFightPawn* refObject, const UInputBufferComponent* inputBuffer)
{

	FInputValidationResult InputResult = CheckSequence(refObject, inputBuffer->GetInputBuffer(), inputBuffer->GetBufferLockState());
	//InputResult.IsCurrentInputValid = CheckCurrentInput(inputBuffer->GetCurrentInput());
	InputResult.IsCurrentInputValid = CheckBufferWithCurrentInput(refObject, inputBuffer->GetInputBuffer(), inputBuffer->GetCurrentInput());
	return InputResult;
}

FInputValidationResult UInputCondition::CheckSequence(AFightPawn* refObject, const TArray<UBufferInputItem*>& inputBuffer, EBufferLockState lockState)
{
	FInputValidationResult result;

	if (InputSequences.Num() == 0)
	{
		result.SequenceResultType = ESequenceCompletionType::NO_SEQUENCE;
		return result;
	}

	if (lockState != EBufferLockState::Unlocked)
	{
		result.SequenceResultType = ESequenceCompletionType::INVALID_SEQUENCE;
		return result;
	}

	for (UInputSequence* sequence : InputSequences)
	{
		if (UInputUtility::ValidateInputSequence(refObject, inputBuffer, sequence))
		{
			result.SequenceResultType = ESequenceCompletionType::VALID_SEQUENCE;
			result.bMotionLock = true; //TODO Only Do this for tap sequences to not effect every QCF
			return result;
		}
	}

	result.SequenceResultType = ESequenceCompletionType::INVALID_SEQUENCE;
	return result;
}

bool UInputCondition::CheckCurrentInput(const UBufferInputItem* currentInput)
{
	if (currentInput == nullptr)
		return false;

	for (int i = 0; i < ValidDirections.Num(); i++)
	{
		if (UInputUtility::ValidateInputDirection(currentInput, ValidDirections[i].RequiredDirections) == true)
		{
			if (ValidDirections[i].ValidStates.Num() > 0)
			{
				if (UInputUtility::ValidateInputState(currentInput->DirectionAtom, ValidDirections[i].ValidStates) == true)
				{
					break;
				}
			}		
			else
				break;
		}

		if (i >= ValidDirections.Num() - 1)
			return false;
	}

	for (FButtonCondition button : RequiredButtons)
	{
		if (UInputUtility::ValidateInputState(currentInput->InputAtoms[(int)button.RequiredButton], button.ValidStates) == false)
			return false;
	}
	return true;
}

bool UInputCondition::CheckBufferWithCurrentInput(AFightPawn* refObject, const TArray<UBufferInputItem*>& inputBuffer, const UBufferInputItem* currentInput)
{
	if (currentInput == nullptr)
		return false;

	for (int i = 0; i < ValidDirections.Num(); i++)
	{
		if (UInputUtility::ValidateInputDirection(currentInput, ValidDirections[i].RequiredDirections) == true)
		{
			if (ValidDirections[i].ValidStates.Num() > 0)
			{
				if (UInputUtility::ValidateInputState(currentInput->DirectionAtom, ValidDirections[i].ValidStates) == true)
				{
					break;
				}
			}
			else
				break;
		}

		if (i >= ValidDirections.Num() - 1)
			return false;
	}
	for (FButtonCondition button : RequiredButtons)
	{
		if (UInputUtility::SearchBufferForButton(refObject,inputBuffer,button, refObject->GameInstance->MotionLifeTime) == false)
			return false;
	}
	return true;
}

