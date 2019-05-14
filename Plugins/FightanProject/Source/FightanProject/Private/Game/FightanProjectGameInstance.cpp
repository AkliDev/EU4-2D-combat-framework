// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/FightanProjectGameInstance.h"

UFightanProjectGameInstance::UFightanProjectGameInstance()
{
	 MotionLifeTime = 0.3f;
	 ValidTimeBetweenInputsInSequence = 0.2f;
	 ValidHoldTimePerInputInSequence = 0.2f;

	 BaseGravity = 1;
}
