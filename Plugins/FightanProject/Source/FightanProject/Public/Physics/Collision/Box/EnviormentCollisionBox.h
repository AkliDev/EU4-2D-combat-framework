// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Physics/Collision/Box/PhysicsBoxComponent.h"
#include "EnviormentCollisionBox.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = "Collision", hidecategories = (Object, LOD, Lighting, TextureStreaming), editinlinenew, meta = (DisplayName = "Enviorment Collision Box", BlueprintSpawnableComponent))
class FIGHTANPROJECT_API UEnviormentCollisionBox : public UPhysicsBoxComponent
{
	GENERATED_BODY()

public:
	UEnviormentCollisionBox();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
