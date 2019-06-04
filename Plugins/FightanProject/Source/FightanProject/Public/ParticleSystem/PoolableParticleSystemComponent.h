// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Particles/ParticleSystemComponent.h"
#include "PoolableParticleSystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTANPROJECT_API UPoolableParticleSystemComponent : public UParticleSystemComponent
{
	GENERATED_BODY()
protected:
	friend class UVFXManager;

	int32 bInUse : 1;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void Init(UParticleSystem* particle, FVector position, FRotator rotation, FVector scale);
	
};
