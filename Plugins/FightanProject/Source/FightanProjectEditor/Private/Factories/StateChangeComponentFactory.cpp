// Fill out your copyright notice in the Description page of Project Settings.


#include "StateChangeComponentFactory.h"
#include "StateMachine/StateChangeComponent.h"

UStateChangeComponentFactory::UStateChangeComponentFactory(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	SupportedClass = UStateChangeComponent::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UStateChangeComponentFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UStateChangeComponent>(InParent, InClass, InName, Flags);
}

bool UStateChangeComponentFactory::ShouldShowInNewMenu() const
{
	return true;
}
