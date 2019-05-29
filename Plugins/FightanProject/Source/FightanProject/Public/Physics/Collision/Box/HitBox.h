// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Physics/Collision/Box/TraceBox.h"
#include "HitBox.generated.h"

/**
 *
 */
class AFightPawn;
UCLASS()
class FIGHTANPROJECT_API UHitBox : public UTraceBox
{
	GENERATED_BODY()

public:
	UHitBox();
protected:
	friend class UBoxDataHandlerComponent;
	friend class UHitManager;
	UPROPERTY(EditAnywhere)
		TArray<AFightPawn*> HitPawns;

	virtual void Deactivate() override;

};
