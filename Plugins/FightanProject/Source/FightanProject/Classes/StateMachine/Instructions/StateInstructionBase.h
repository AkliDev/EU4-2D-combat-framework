// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Classes/Engine/DataTable.h"
#include "Classes/Sound/SoundWave.h"

#include "StateMachine/Events/EventEnums.h"

#include "StateInstructionBase.generated.h"

class AFightPawn;
class UFightPawnState;
/**
 *
 */
USTRUCT(Blueprintable)
struct FIGHTANPROJECT_API FInstructionParameter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instruction parameter")
		int Int;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instruction parameter")
		float Float;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instruction parameter")
		FVector Vector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instruction parameter")
		USoundWave* Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instruction parameter")
		UFightPawnState* State;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instruction parameter")
		Events Event;
};

UCLASS(Blueprintable)
class FIGHTANPROJECT_API UStateInstructionBase : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "State Instruction")
		 void Execute(AFightPawn* refObject, FInstructionParameter params);
};


USTRUCT()
struct FIGHTANPROJECT_API FInstruction : public FTableRowBase
{
	GENERATED_BODY()

public:
	//Instructions to execute
	UPROPERTY(EditAnywhere)
		TSubclassOf<UStateInstructionBase> Instruction;

	//Paramws for instruction;
	UPROPERTY(EditAnywhere)
		FInstructionParameter Params;
};

USTRUCT()
struct FIGHTANPROJECT_API FInstructionRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	//Instructions to execute
	UPROPERTY(EditAnywhere)
		TArray<FInstruction> Instructions;

	//When to execute instruction
	UPROPERTY(EditAnywhere)
		float Time;
};