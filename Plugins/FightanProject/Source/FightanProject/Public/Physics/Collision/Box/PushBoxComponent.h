// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Physics/Collision/Box/PhysicsBoxComponent.h"
#include "PushBoxComponent.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTransformChange);

UCLASS()
class FIGHTANPROJECT_API UPushBoxComponent : public UPhysicsBoxComponent
{
	GENERATED_BODY()

		//void SetBoxExtent(FVector InBoxExtent, bool bUpdateOverlaps = true) override;
public:
	UPushBoxComponent();
protected:
	virtual void OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport)override;
public:
	FOnTransformChange OnTransformChange;
};
