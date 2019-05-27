// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachineResults.generated.h"

//Forward declaration to prevent circular dependency 
class UFightPawnState;
/**
 *
 */

UENUM()
enum class ESequenceCompletionType : uint8
{
	// Sequence was given but the buffer did not pass validation
	INVALID_SEQUENCE,

	// Sequence was given and the buffer passed validation
	VALID_SEQUENCE,

	// No sequence was given
	NO_SEQUENCE
};

USTRUCT()
struct FIGHTANPROJECT_API FInputValidationResult
{
	GENERATED_BODY()

public:
	FInputValidationResult();

	UPROPERTY()
		ESequenceCompletionType SequenceResultType;

	UPROPERTY()
		uint32 IsCurrentInputValid : 1;

	UPROPERTY()
		uint32 bMotionLock : 1;
	
	bool IsInputValid();
};

USTRUCT()
struct FIGHTANPROJECT_API FStateMachineResult
{
	GENERATED_BODY()

public:
	FStateMachineResult();
	UPROPERTY()
		FInputValidationResult InputValidationResult;

	UPROPERTY()
		UFightPawnState* DestinationState;
		
	UPROPERTY()
		uint32 bClearBuffer : 1;
};