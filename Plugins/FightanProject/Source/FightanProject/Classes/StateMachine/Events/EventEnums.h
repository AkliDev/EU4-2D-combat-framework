// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventEnums.generated.h"

UENUM(Blueprintable, Meta = (Bitflags))
enum class Events : uint8
{
	ON_COLLISION_UP,
	ON_COLLISION_DOWN,
	ON_COLLISION_BEHIND,
	ON_COLLISION_FRONT,

	ON_VELOCITY_FLIP_X,
	ON_VELOCITY_FLIP_Z
};
