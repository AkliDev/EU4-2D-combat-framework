// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "FightPawnStateFactory.generated.h"

/**
 *
 */

UCLASS()
class UFightPawnStateFactory : public UFactory
{
	GENERATED_BODY()
public:
	UFightPawnStateFactory(const FObjectInitializer& ObjectInitializer);
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool ShouldShowInNewMenu() const override;

};
