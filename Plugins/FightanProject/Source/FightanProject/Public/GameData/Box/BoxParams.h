// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Classes/Sound/SoundWave.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystem.h"
#include "StateMachine/Instructions/StateInstructionBase.h"
#include "BoxParams.generated.h"


/**
 *
 */
UENUM(Blueprintable, Meta = (Bitflags))
enum class BoxType : uint8
{
	HIT_BOX,
	HURT_BOX
};

USTRUCT()
struct FIGHTANPROJECT_API FBoxParams
{
	GENERATED_BODY()

public:

	FBoxParams();

	UPROPERTY(EditAnywhere)
		FVector Position;
	UPROPERTY(EditAnywhere)
		FVector Extent;
	UPROPERTY(EditAnywhere)
		float LifeTime;
};

UENUM(Blueprintable, Meta = (Bitflags))
enum class AttackType : uint8
{
	Normal
};

USTRUCT()
struct FIGHTANPROJECT_API FHitBoxParams
{
	GENERATED_BODY()

public:

	FHitBoxParams();

	UPROPERTY(EditAnywhere)
		AttackType Type;

	UPROPERTY(EditAnywhere)
		float HitStunTime;

	UPROPERTY(EditAnywhere)
		float HitRumbleIntensity;

	UPROPERTY(EditAnywhere)
		float HitRumbleSpeed;

	UPROPERTY(EditAnywhere)
		FVector GroundKnockBackVelocity;

	UPROPERTY(EditAnywhere)
		FVector2D HitStop;

	UPROPERTY(EditAnywhere)
	TArray<FInstruction> HitInstrucion;
};
