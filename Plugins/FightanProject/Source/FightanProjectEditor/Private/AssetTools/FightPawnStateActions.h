// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "Templates/SharedPointer.h"
#include "FightanProjectEditor.h"

#include "StateMachine/FightPawnState.h"



/**
 * 
 */
class FightPawnStateActions : public FAssetTypeActions_Base
{
public:
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_FightPawnState", "Fight Pawn State"); }
	virtual uint32 GetCategories() override { return MY_AssetCategory; }
	virtual FColor GetTypeColor() const override { return FColor(127, 255, 255); }
	virtual FText GetAssetDescription(const FAssetData &AssetData) const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_FightPawnState", "State data holder for FightPawn"); }
	virtual UClass* GetSupportedClass() const override { return UFightPawnState::StaticClass(); }
};
