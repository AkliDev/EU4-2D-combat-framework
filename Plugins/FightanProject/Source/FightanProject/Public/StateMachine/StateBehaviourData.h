// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Character/FightPawn.h"
#include "Instructions/StateInstructionBase.h"
#include "Engine/DataTable.h"
#include "StateBehaviourData.generated.h"

/**
 *
 */
UCLASS()
class FIGHTANPROJECT_API UStateBehaviourData : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		TArray<FInstruction> OnEnterInstructions;
	UPROPERTY(EditAnywhere)
		TArray<FInstruction> LoopInstructions;
	UPROPERTY(EditAnywhere)
		TArray<FInstruction> OnExitInstructions;

	UPROPERTY(EditAnywhere)
		UDataTable* TickInstructionTables;

	UPROPERTY(EditAnywhere)
		UDataTable* BoxInstructionTables;

};
