// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/InputBuffer/BufferItem.h"
#include "Input/InputEnums.h"
#include "BufferInputItem.generated.h"

class UInputUtility;
/**
 *
 */

USTRUCT()
struct FIGHTANPROJECT_API FInputAtom
{
	GENERATED_BODY()
public:
	FInputAtom();

	UPROPERTY(EditAnywhere)
		float HoldTime;

	// When true this input will not be read by the buffer parser because it is already used / Consumed
	UPROPERTY(EditAnywhere)
		uint32 Consumed : 1;
	UPROPERTY(EditAnywhere)
		InputState State;

	// returns weather the input is consumed
	bool IsConsumed();

	//Consumes the input when called
	void Consume();

	//Counts up how long the input is held for and sets it to either down or held depending on its state
	void Hold(float DeltaTime);

	//Sets the input to released or not pressed depending on its state
	void ReleaseHold();

	//forces the button to be held down
	void ForceHold();

	//resetproperties of this input atom
	void Reset();
};

USTRUCT()
struct FIGHTANPROJECT_API FInputDirectionAtom : public FInputAtom
{
	GENERATED_BODY()
private:

public:
	FInputDirectionAtom();

	UPROPERTY(EditAnywhere)
	DirectionNotation Direction;
};

UCLASS()
class FIGHTANPROJECT_API UBufferInputItem : public UBufferItem
{
	GENERATED_BODY()

public:
	UBufferInputItem();
	UBufferInputItem(uint32 atomAmount);
	void Init(uint32 atomAmount);

	//Updates input with given input bitflags and previous input bitflags
	UFUNCTION()
		void UpdateInputItem(uint32 inputBitflag, uint32 previousInputBitflag, float deltaTime);

	//Assign operator overload sets all field to the one given in the param
	UBufferInputItem& operator= (UBufferInputItem* BUfferInputItem);

	//All the input atoms for this buffer item each for every in game button
	UPROPERTY(EditAnywhere)
		TArray<FInputAtom> InputAtoms;

	//The held direction of this buffer item
	UPROPERTY(EditAnywhere)
		FInputDirectionAtom DirectionAtom;

	//Since directions can have negative edge we also store the previous direction
	UPROPERTY(EditAnywhere)
		FInputDirectionAtom ReleasedDirectionAtom;

	//Input bitflag of the input
	UPROPERTY(EditAnywhere)
		uint32 InputBitflag;
}; 