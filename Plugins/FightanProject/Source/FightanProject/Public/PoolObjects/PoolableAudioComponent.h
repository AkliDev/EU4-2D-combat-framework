// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/AudioComponent.h"
#include "PoolableAudioComponent.generated.h"

/**
 * 
 */
UCLASS()
class FIGHTANPROJECT_API UPoolableAudioComponent : public UAudioComponent
{
	GENERATED_BODY()

protected:
	friend class USFXManager;

	UPROPERTY(EditAnywhere)
		uint32 bInUse : 1;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void SetInactive();

public:

	virtual void Init(USoundWave* soundWave, FVector position);

};