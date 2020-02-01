// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/InputUtility.h"
#include "Input/Condition/InputCondition.h"
#include "Input/InputBuffer/BufferInputItem.h"


/// <summary>Converts the given input bitflag to fighting game direction notation</summary>
/// <param name="sel">Bitflag that reprisents the players input</param>  
/// <returns>DirectionNotation, Numpad representation of directional input</returns>  
DirectionNotation UInputUtility::ConvertInputBitflagToDirectionNotation(uint32 inputBitflag)
{
	//5+(raw horizontal axis)+(3*raw vertical axis) is the magic FG notation formula
	uint8 direction = 5;

	if (inputBitflag & (1 << (32 - ((int32)CardinalDirection::NUM - (int32)CardinalDirection::UP))))
		direction += 3;
	if (inputBitflag & (1 << (32 - ((int32)CardinalDirection::NUM - (int32)CardinalDirection::DOWN))))
		direction -= 3;
	if (inputBitflag & (1 << (32 - ((int32)CardinalDirection::NUM - (int32)CardinalDirection::LEFT))))
		direction -= 1;
	if (inputBitflag & (1 << (32 - ((int32)CardinalDirection::NUM - (int32)CardinalDirection::Right))))
		direction += 1;

	return (DirectionNotation)direction;
}

/// <summary>Converts the given input bitflag to a string reprisentation</summary>
/// <param name="sel">Bitflag that reprisents the players input</param>  
/// <returns>String of 1's and 0's</returns> 
FString UInputUtility::ConvertInputBitflagToBinaryString(uint32 inputBitflag)
{
	std::bitset<32> x(inputBitflag);
	FString InputString;

	for (int i = 0; i < x.size(); i++)
	{
		InputString.AppendInt(x[i]);
	}

	return InputString;
}

uint32 UInputUtility::SwapBits(uint32 n, uint32 p1, uint32 p2)
{
	/* Move p1'th to rightmost side */
	uint32 bit1 = (n >> p1) & 1;

	/* Move p2'th to rightmost side */
	uint32 bit2 = (n >> p2) & 1;

	/* XOR the two bits */
	uint32 x = (bit1 ^ bit2);

	/* Put the xor bit back to their original positions */
	x = (x << p1) | (x << p2);

	/* XOR 'x' with the original number so that the
	   two sets are swapped */
	uint32 result = n ^ x;

	return result;
}

/// <summary>Checks if the the given sequence is found within the given input buffer</summary>
/// <param name="sel">Reference to subject pawn, an input buffer to validate preferably one owned by the subject pawn and pointer so sequence to match with the input buffer</param>  
/// <returns>Bool, whether the input sequence was found withing the given input buffer</returns> 
bool UInputUtility::ValidateInputSequence(AFightPawn* refObject, const TArray<UBufferInputItem*>& inputBuffer, UInputSequence* sequence)
{
	if (refObject->GameInstance == nullptr)
		return false;

	if (sequence == nullptr)
		return true;
	
	//copy valid time between inputs from the settings in the game instance through the refObject
	float validTimeBetweenInputsInSequence = refObject->GameInstance->ValidTimeBetweenInputsInSequence;

	//copy valid hold time per input in sequence from the settings in the game instance through the refObject
	float validHoldTimePerInputInSequence = refObject->GameInstance->ValidHoldTimePerInputInSequence;

	//index input in the Sequence we are checking NOTE we start at sequence->Sequence.Num() - 1 because we check the sequence in the buffer backwards starting at the most resent input 
	int currentSequenceItemIndex = sequence->Sequence.Num() - 1;

	//index of input item in the buffer from where we start checking for the sequence
	int inputBufferItemToCheck = FindFirstValidBufferItemIndex(refObject, inputBuffer, sequence->Sequence[currentSequenceItemIndex], refObject->GameInstance->MotionLifeTime);

	//if the input item to check is out of the range of the buffer then we will set this variable to the last index of the buffer else we will set this to the inputBufferItemToCheck
	UBufferInputItem* LastValidInputInBuffer = inputBufferItemToCheck > inputBuffer.Num() ? inputBuffer[inputBufferItemToCheck] : inputBuffer[inputBuffer.Num() - 1];

	//iterate through the input buffer from the first valid index in the input buffer 
	for (int i = inputBufferItemToCheck; i < inputBuffer.Num(); i++)
	{
		//if the input item to check is a nullptr than we skip it
		if (inputBuffer[i] == nullptr)
			continue;

		//if the input item to check has on of the forbidden Directions then the sequence is invalid this we stop looking for this sequence
		if (ValidateInputDirections(inputBuffer[i], sequence->ForbiddenDirectons) && sequence->ForbiddenDirectons.Num() > 0)
			break;

		if (ValidateInputDirection(inputBuffer[i], sequence->Sequence[currentSequenceItemIndex].RequiredDirecton))
		{
			if (currentSequenceItemIndex < sequence->Sequence.Num() - 1)
				//if the time difference between this input and the previous valid input in the buffer is greater than the validTimeBetweenInputsInSequence, then the sequence in the buffer is invalid so we break out of the loop
				if (inputBuffer[i]->GetTimeDifferenceWithOtherItem(LastValidInputInBuffer) > validTimeBetweenInputsInSequence)
					break;

			if (sequence->Type == SequneceType::TAP)
			{
				if (ValidateInputState(inputBuffer[i]->DirectionAtom, InputState::PRESSED) == false)
					break;

				if (i > 0)
					if (inputBuffer[i - 1]->ReleasedDirectionAtom.HoldTime > validHoldTimePerInputInSequence)
					{
						GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Emerald, FString::SanitizeFloat(inputBuffer[i - 1]->ReleasedDirectionAtom.HoldTime));
						break;
					}
			}
			else if (currentSequenceItemIndex > 0 && currentSequenceItemIndex < sequence->Sequence.Num() - 1 && i > 0)
			{
				if (inputBuffer[i - 1]->ReleasedDirectionAtom.HoldTime > validHoldTimePerInputInSequence)
				{
					GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Emerald, FString::SanitizeFloat(inputBuffer[i - 1]->ReleasedDirectionAtom.HoldTime));
					break;
				}
			}

			if (currentSequenceItemIndex == 0)
				return true;

			currentSequenceItemIndex--;
			LastValidInputInBuffer = inputBuffer[i];
		}
	}

	return false;
}

/// <summary>Finds the index of the required input in the inbut buffer</summary>
/// <param name="sel">Reference to subject pawn, an input buffer to search for the first input preferably one owned by the subject pawn and the input stamp to search</param>  
/// <returns>int, Index at which the first valid input is found. if none is found the count to the input buffer is given to make for loops using this return value immediately exit their iteration</returns> 
int UInputUtility::FindFirstValidBufferItemIndex(AFightPawn* refObject, const TArray<UBufferInputItem*>& inputBuffer, FInputStamp inputStamp, float motionLifeTime)
{	
	//Iterate through the given input buffer
	for (int i = 0; i < inputBuffer.Num(); i++)
	{
		//cache the age of the current input item we are checking
		float inputAge = inputBuffer[i]->GetInputAgeFromBeginTime(UKismetSystemLibrary::GetGameTimeInSeconds(refObject));

		/*we return the index position of the input item in the buffer if the input item corresponds with the given input stamp (we only check direction ATM)
		and if the age of the current input is less then the motion life time*/
		if (ValidateInputDirection(inputBuffer[i], inputStamp.RequiredDirecton) &&
			inputAge < motionLifeTime)
		{
			return i;
		}
	}
	//if the input stamp did not correspond with any input item in the given buffer then we return the length of the buffer  
	return inputBuffer.Num();
}

bool UInputUtility::SearchBufferForButton(AFightPawn* refObject, const TArray<UBufferInputItem*>& inputBuffer, FButtonCondition buttonCondition, float motionLifeTime)
{
	for (int i = 0; i < inputBuffer.Num(); i++)
	{
		//cache the age of the current input item we are checking
		float inputAge = inputBuffer[i]->GetInputAgeFromBeginTime(UKismetSystemLibrary::GetGameTimeInSeconds(refObject));

		if (ValidateInputState(inputBuffer[i]->InputAtoms[(int)buttonCondition.RequiredButton], buttonCondition.ValidStates) &&
			inputAge < motionLifeTime)
		{
			return true;
		}
	}

	return false;
}

/// <summary>checks if the given direction corrisponds with the direction of the given input item</summary>
/// <param name="sel">input item to check, direction to check for</param>  
/// <returns>bool, weather the direction corresponds with the direction of the input item  </returns> 
bool UInputUtility::ValidateInputDirection(const UBufferInputItem* currentInput, const DirectionNotation requiredCurrentHoldDirection)
{
	//if the direction of current input corresponds with one of the valid direction we return true
	if (currentInput != nullptr)
		if (currentInput->DirectionAtom.Direction == requiredCurrentHoldDirection)
			return true;

	return false;
}

/// <summary>checks if  one of the the givens direction corrisponds with the direction of the given input item</summary>
/// <param name="sel">input item to check, directions to check for</param>  
/// <returns>bool, weather  one of the given directions corresponds with the direction of the input item  </returns> 
bool UInputUtility::ValidateInputDirections(const UBufferInputItem* currentInput, const TArray<DirectionNotation>& validHoldDirections)
{	//if no input directions are given then they are not required so we return true
	if (validHoldDirections.Num() == 0)
		return true;

	//iterates through the valid hold directions and if the direction of current input corresponds with one of the valid direction we return true
	for (DirectionNotation notation : validHoldDirections)
	{
		if (currentInput != nullptr)
			if (currentInput->DirectionAtom.Direction == notation)
			{
				return true;
			}
	}

	return false;
}

//bool UInputUtility::ValidateInputButton(const UBufferInputItem* currentInput, const Button ValidButton)
//{
//	uint32 bitmask = 1 << (uint32)ValidButton;
//	return true;
//}

/// <summary>Checks weather the the given buttons are pressed in the given input item </summary>
/// <param name="sel">input buffer item to check, bottons to validate</param>  
/// <returns>bool, weather  one of the given directions corresponds with the direction of the input item  </returns> 
bool UInputUtility::ValidateInputButtons(const UBufferInputItem* currentInput, const TArray<Button>& requiredCurrentButtons)
{
	//create an empty bit mask
	uint32 bitmask = 0;
	// copy bitflag from input item
	uint32 currentInputBitFlag = currentInput->InputBitflag;

	//itereate through the given buttons and set the corresponding bits in the bitmak
	for (Button button : requiredCurrentButtons)
	{
		bitmask |= (1 << (uint32)button);
	}

	//sets the last 4 bits of currentInputBitFlag to 0 because we only want to check the bits that represent the buttons and not the cardinal directions 
	for (uint8 i = 0; i < (uint8)CardinalDirection::NUM; i++)
	{
		//set last 4 bits in currentInputBitFlag to 1.
		currentInputBitFlag |= (1 << (32 - (int32)CardinalDirection::NUM + (i)));
		//then flip the last 4 bits in currentInputBitFlag so that they become 0
		currentInputBitFlag ^= (1 << (32 - (int32)CardinalDirection::NUM + (i)));
	}

	return ((currentInputBitFlag & bitmask) == bitmask);
}

bool UInputUtility::ValidateInputState(const FInputAtom inputAtom, const InputState validButtonState)
{
	if (inputAtom.State == validButtonState)
		return true;

	return false;
}

/// <summary>Checks of the state of the given input atom is the same  </summary>
/// <param name="sel">input buffer item to check, bottons to validate</param>  
/// <returns>bool, weather  one of the given directions corresponds with the direction of the input item  </returns> 
bool UInputUtility::ValidateInputState(const FInputAtom inputAtom, const TArray<InputState>& validButtonStates)
{
	//if no valid button state is given then the valid state of PRESSED is assumed
	if (validButtonStates.Num() == 0)
	{
		if (inputAtom.State == InputState::PRESSED)
			return true;
		else
			return false;
	}

	//Iterate through the valid states
	for (InputState state : validButtonStates)
	{
		if (inputAtom.State == state)
		{
			return true;
		}
	}

	return false;
}

