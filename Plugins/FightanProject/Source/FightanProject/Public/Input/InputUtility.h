// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"


#include "Input/InputEnums.h"
#include <bitset>
#include "Kismet/KismetSystemLibrary.h"

#include "Character/FightPawn.h"
#include "Input/Condition/InputCondition.h"
#include "Input/InputBuffer/BufferInputItem.h"
#include "InputUtility.generated.h"

/**
 *
 */
UCLASS()
class FIGHTANPROJECT_API UInputUtility : public UObject
{
	GENERATED_BODY()

public:
	///Input convertion///

	//Converts Input Bitflag To Fighting Game DirectionNotation
	static DirectionNotation ConvertInputBitflagToDirectionNotation(uint32 inputBitflag);

	//Converts Input Bitflag To BinaryString
	static FString ConvertInputBitflagToBinaryString(uint32 inputBitflag);

	static uint32 SwapBits(uint32 n, uint32 p1, uint32 p2);

	///Input validation///

	//Iterates through the buffer and compares it to a sequence 
	static bool ValidateInputSequence(AFightPawn* refObject, const TArray<UBufferInputItem*>& inputBuffer, UInputSequence* sequence);
	
	//searches the buffer for the given input stamp and returns its index
	static int FindFirstValidBufferItemIndex(AFightPawn* refObject, const TArray<UBufferInputItem*>& inputBuffer, FInputStamp inputStamp);

	//returns true if the given input item direction is the same as the valid direction
	static bool ValidateInputDirection(const UBufferInputItem* currentInput, const DirectionNotation validCurrentHoldDirection);

	//returns true if the given input item direction is the same as one of the valid directions given
	static bool ValidateInputDirections(const UBufferInputItem* currentInput, const TArray<DirectionNotation>& validHoldDirections);

	//returns true if the buttons of the given input item bitflag corresponds with the valid input buttons
	//////static bool ValidateInputButton(const UBufferInputItem* currentInput, const Button validCurrentButton);
	//returns true if the given input item bitflag corresponds with the buttons given
	static bool ValidateInputButtons(const UBufferInputItem* currentInput, const TArray<Button>& validCurrentButtons);


	static bool ValidateInputState(const FInputAtom inputAtom, const InputState validButtonState);
	//returns true if the given input state corresponds with on of the valid input states
	static bool ValidateInputState(const FInputAtom inputAtom, const TArray<InputState>& validButtonStates);
};
