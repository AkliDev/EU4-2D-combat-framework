// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Physics/Collision/Box/TraceBox.h"
#include "HurtBox.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTANPROJECT_API UHurtBox : public UTraceBox
{
	GENERATED_BODY()
public:
	UHurtBox();
};
