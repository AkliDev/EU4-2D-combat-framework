// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Physics/Collision/Box/FGCollisionBoxBase.h"
#include "GameData/Box/BoxInstruction.h"
#include "TraceBox.generated.h"

/**
 *
 */


UCLASS()
class FIGHTANPROJECT_API UTraceBox : public UFGCollisionBoxBase
{
	GENERATED_BODY()

public:
	UTraceBox();

protected:

	friend class UBoxDataHandlerComponent;
	float LifeTime;
	int32 bInUse : 1;

	void Deactivate();

public:

	virtual void Init(FBoxParams& params);
};