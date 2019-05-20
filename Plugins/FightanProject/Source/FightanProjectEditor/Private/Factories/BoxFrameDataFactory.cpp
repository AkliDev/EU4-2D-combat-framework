// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxFrameDataFactory.h"
#include "GameData/Box/BoxFrameData.h"

UBoxFrameDataFactory::UBoxFrameDataFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UBoxFrameData::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UBoxFrameDataFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UBoxFrameData>(InParent, InClass, InName, Flags);
}

bool UBoxFrameDataFactory::ShouldShowInNewMenu() const
{
	return true;
}
