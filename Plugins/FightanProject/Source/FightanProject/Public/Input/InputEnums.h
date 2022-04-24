// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputEnums.generated.h"

UENUM(Blueprintable, Meta = (Bitflags))
enum class CardinalDirection  : uint8
{
	UP,
	DOWN,
	LEFT,
	Right,
	NUM		UMETA(Hidden)
};

UENUM(Blueprintable, Meta = (Bitflags))
enum class DirectionNotation : uint8
{
	NONE = 0,
	DOWN_BACK = 1,
	DOWN,
	DOWN_FORWARD,
	BACK,
	NEUTRAL,
	FORWARD,
	UP_BACK,
	UP,
	UP_FORWARD,
	NUM = UP_FORWARD	UMETA(Hidden)
};

UENUM()
enum class InputState : int8
{
	RELEASED = -1,
	NOT_PRESSED = 0,
	PRESSED = 1,
	HELD = 2
};

UENUM(Blueprintable, Meta = (Bitflags))
enum class FaceButton : uint8
{
	BUTTON1,
	BUTTON2,
	BUTTON3,
	BUTTON4,
	BUTTON5,
	BUTTON6,
	NUM		UMETA(Hidden)
};

