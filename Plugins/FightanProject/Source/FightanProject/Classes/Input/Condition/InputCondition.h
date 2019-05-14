// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Character/FightPawn.h"
#include "Input/InputBuffer/InputBufferComponent.h"
#include "Input/InputBuffer/BufferInputItem.h"
#include "Input/InputEnums.h"
#include "StateMachine/StateMachineResults.h"
#include "InputCondition.generated.h"

class UInputUtility;
/**
 *
 */

USTRUCT()
struct FIGHTANPROJECT_API FButtonCondition
{
	GENERATED_BODY()

public:
	//Button Input
	UPROPERTY(EditAnywhere)
		Button RequiredButton;

	//Button State
	UPROPERTY(EditAnywhere)
		TArray<InputState> ValidStates;
};

USTRUCT()
struct FIGHTANPROJECT_API FInputStamp
{
	GENERATED_BODY()

public:
	//Direction Input
	UPROPERTY(EditAnywhere)
		DirectionNotation RequiredDirecton;

	//Button Input
	UPROPERTY(EditAnywhere)
		TArray<Button> RequiredButtons;
};

enum class SequneceType : uint8
{
	ADJACENT,
	TAP,
	CHARGE
};

UCLASS()
class FIGHTANPROJECT_API UInputSequence : public UDataAsset
{
	GENERATED_BODY()
public:
	//Sequence of Direction + Buttons  
	UPROPERTY(EditAnywhere)
		TArray<FInputStamp> Sequence;

	//Forbidden Directions that make a sequence invalid
	UPROPERTY(EditAnywhere)
		TArray<DirectionNotation> ForbiddenDirectons;

	//Forbidden Buttons that make a sequence invalid
	UPROPERTY(EditAnywhere)
		TArray<FButtonCondition>  ForbiddenButtons;

	SequneceType Type;
};

UCLASS()
class FIGHTANPROJECT_API UTapSequence : public UInputSequence
{
	GENERATED_BODY()
public:
	UTapSequence();
};

UCLASS()
class FIGHTANPROJECT_API UInputCondition : public UDataAsset
{
	GENERATED_BODY()

protected:
	//Required 1 Sequence for this condition to be true;
	UPROPERTY(EditAnywhere)
		TArray <UInputSequence*> InputSequences;

	//Required current direction held for this condition to be true
	UPROPERTY(EditAnywhere)
		TArray<DirectionNotation> ValidCurrentHoldDirections;

	//Required current button pressed for this condition to be true
	UPROPERTY(EditAnywhere)
		TArray<FButtonCondition> RequiredCurrentButtons;
	
public: 
	//Calls this class private validation methods
	FInputValidationResult ValidateInput(AFightPawn* refObject, const UInputBufferComponent* InputBuffer);

private:
	//Returns true if the sequence with the given input buffer is valid
	FInputValidationResult CheckSequence(AFightPawn* refObject, const TArray<UBufferInputItem*>& inputBuffer, EBufferLockState lockState);
	//Returns true if the input with the current given input is valid
	bool CheckCurrentInput(const UBufferInputItem* currentInput);
};
