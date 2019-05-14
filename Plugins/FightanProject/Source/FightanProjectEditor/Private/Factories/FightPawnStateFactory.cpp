// Fill out your copyright notice in the Description page of Project Settings.


#include "FightPawnStateFactory.h"
#include "StateMachine/FightPawnState.h"

UFightPawnStateFactory::UFightPawnStateFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UFightPawnState::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UFightPawnStateFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UFightPawnState>(InParent, InClass, InName, Flags);
}

bool UFightPawnStateFactory::ShouldShowInNewMenu() const
{
	return true;
}
