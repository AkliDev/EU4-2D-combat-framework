// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/InputBuffer/BufferInputItem.h"
#include "Input/InputUtility.h"

//BufferInputItem
UBufferInputItem::UBufferInputItem()
{

}

UBufferInputItem::UBufferInputItem(uint32 atomAmount)
{
	Init(atomAmount);
}


/// <summary>Sets atom amount to the amount given in params. should be the amount of buttons</summary>
void UBufferInputItem::Init(uint32 atomAmount)
{
	InputAtoms.SetNum(atomAmount);
}

//void UBufferInputItem::Init(uint32 atomAmount)
//{
//	for (uint32 i = 0; i < atomAmount; i++)
//	{
//		InputAtoms.Add(NewObject<UInputAtom>());
//	}
//
//	DirectionAtom = NewObject<UInputDirectionAtom>();
//}

/// <summary>Updates all input atoms of this input item</summary>
/// <param name="sel">input bitflag to update with, input bitflag of the previous frame, Time delta</param>  
/// <returns>void</returns>  
void UBufferInputItem::UpdateInputItem(uint32 inputBitflag, uint32 previousInputBitflag, float deltaTime)
{
	//Sets the input bitflag of this buffer input item
	InputBitflag = inputBitflag;


	//Iterate through the bits the represents buttons in the input bitflag
	//Compares the bits to the one of the previous Input Bitflag
	for (uint8 i = 0; i < (uint8)FaceButton::NUM; i++)
	{
		uint32 bitmask = 1 << i;
		if (InputBitflag & bitmask)
			InputAtoms[i].Hold(deltaTime);
		if ((InputBitflag & bitmask) != bitmask && (previousInputBitflag & bitmask) == bitmask)
			InputAtoms[i].ReleaseHold();
		if ((InputBitflag & bitmask) != bitmask && (previousInputBitflag & bitmask) != bitmask)
			InputAtoms[i].Reset();
	}

	//Iterate through the bits the represents cardinal direction in the input bitflag
	//Compares the bits to the one of the previous Input Bitflag
	for (uint8 i = (uint8)FaceButton::NUM; i < (uint8)FaceButton::NUM + (uint8)CardinalDirection::NUM; i++)
	{
		uint32 bitmask = (1 << (i - (uint8)FaceButton::NUM + 32 - (uint8)CardinalDirection::NUM));
		if (InputBitflag & bitmask)
			InputAtoms[i].Hold(deltaTime);
		if ((InputBitflag & bitmask) != bitmask && (previousInputBitflag & bitmask) == bitmask)
			InputAtoms[i].ReleaseHold();
		if ((InputBitflag & bitmask) != bitmask && (previousInputBitflag & bitmask) != bitmask)
			InputAtoms[i].Reset();
	}

	//convert the input bitflags to a notation to compare them later
	DirectionNotation currentDirection = UInputUtility::ConvertInputBitflagToDirectionNotation(inputBitflag);
	DirectionNotation previousDirection = UInputUtility::ConvertInputBitflagToDirectionNotation(previousInputBitflag);

	ReleasedDirectionAtom = DirectionAtom;
	DirectionAtom.Direction = currentDirection;
	
	//if the direction is different than the previous direction we reset the direction timer and update the input state
	if(DirectionAtom.Direction != previousDirection)
	{		
		ReleasedDirectionAtom.Hold(deltaTime);
		ReleasedDirectionAtom.ReleaseHold();
		DirectionAtom.Reset();
		DirectionAtom.State = InputState::PRESSED;
	}
	// else we increment the hold time for the direction
	else
	{
		DirectionAtom.Hold(deltaTime);
	}
}

UBufferInputItem& UBufferInputItem::operator=(UBufferInputItem* BUfferInputItem)
{
	BeginTimeStamp = BUfferInputItem->BeginTimeStamp;
	EndTimeStamp = BUfferInputItem->EndTimeStamp;
	InputAtoms = BUfferInputItem->InputAtoms;
	DirectionAtom = BUfferInputItem->DirectionAtom;
	ReleasedDirectionAtom = BUfferInputItem->ReleasedDirectionAtom;
	InputBitflag = BUfferInputItem->InputBitflag;

	return *this;
}

//InputAtom

//Set default value's
FInputAtom::FInputAtom()
{
	HoldTime = 0.0f;
	Consumed = false;
	State = InputState::NOT_PRESSED;
}

/// <summary>returns weather the input atom is used or not</summary>
/// <returns>bool, if the atom is consumed</returns> 
bool FInputAtom::IsConsumed()
{
	//If Button state != Down or Held and the concumed flag is true? then the input is already used and this returns true
	//We don't just return the "Consumed" variable because 
	if ((int8)State > 0 && !Consumed)
	{
		return false;
	}
	return true;
}

/// <summary>Consumes the input atom</summary>
void FInputAtom::Consume()
{
	//Sets Consumed to true
	Consumed = true;
}

/// <summary>Increments hold time of this input atom and sets the buttons state accorsing to the hold time</summary>
/// <param name="sel">Amount to incriment the hold time with</param>  
void FInputAtom::Hold(float DeltaTime)
{
	//if the button is up and you hold it the button is just pressed
	if (State == InputState::NOT_PRESSED || State == InputState::RELEASED)
	{
		State = InputState::PRESSED;

	}
	//If it is already Pressed then the button is held down
	else
	{
		State = InputState::HELD;
		HoldTime += DeltaTime;
	}
}

/// <summary>Sets the state of the buffer item to either RELEASED or NOT_PRESSED depending on it's current state</summary> 
void FInputAtom::ReleaseHold()
{
	//If the button is down and you release it then the button is just released
	if (State == InputState::PRESSED || State == InputState::HELD)
	{
		State = InputState::RELEASED;
		Consumed = false;
	}
	//If the button is just released or not pressed then the button is not pressed
	else
	{
		State = InputState::NOT_PRESSED;
	}
}

///<summary> Force hold to allow for DBFZ style buffer</summary>
void FInputAtom::ForceHold()
{
	State = InputState::HELD;
}

///<summary> This resets the input atom</summary>
void FInputAtom::Reset()
{
	HoldTime = 0.0f;
	State = InputState::NOT_PRESSED;
	Consumed = false;
}

//InputDirectionAtom
FInputDirectionAtom::FInputDirectionAtom()
	:FInputAtom()
{
	Direction = DirectionNotation::NEUTRAL;
}
