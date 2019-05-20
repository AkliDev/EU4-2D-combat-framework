// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "Templates/SharedPointer.h"
#include "FightanProjectEditor.h"

#include "StateMachine/StateChangeComponent.h"

/**
 * 
 */
class StateChangeComponentActions : public FAssetTypeActions_Base
{
public:
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_StateChangeComponent", "State Change Component"); }
	virtual uint32 GetCategories() override { return MY_AssetCategory; }
	virtual FColor GetTypeColor() const override { return FColor(75, 200, 200); }
	virtual FText GetAssetDescription(const FAssetData &AssetData) const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_FightPawnState", "State data holder for FightPawn"); }
	virtual UClass* GetSupportedClass() const override { return UStateChangeComponent::StaticClass(); }
};
