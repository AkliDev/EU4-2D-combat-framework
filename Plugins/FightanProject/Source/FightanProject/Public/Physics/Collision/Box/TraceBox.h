// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Physics/Collision/Box/FGCollisionBoxBase.h"
#include "GameData/Box/BoxParams.h"
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

	UPROPERTY(EditAnywhere)
		float LifeTime;

		int32 bInUse : 1;

	virtual void Deactivate();

public:

	virtual void Init(FBoxParams& params);

	//init for hitboxes to override
	virtual void Init(FBoxParams& params, FHitBoxParams& hitParams);
};