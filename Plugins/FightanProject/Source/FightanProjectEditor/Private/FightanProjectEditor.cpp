// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FightanProjectEditor.h"
#include "AssetToolsModule.h"

#include "IPluginManager.h"
#include "SlateStyleRegistry.h"

#include "AssetTools/FightPawnStateActions.h"
#include "AssetTools/StateChangeComponentActions.h"



#define LOCTEXT_NAMESPACE "FFightanProjectEditorModule"

void FFightanProjectEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	IAssetTools &AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	MY_AssetCategory = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("Fightan")), LOCTEXT("Fightan", "Fightan"));
	{

		TSharedRef<IAssetTypeActions> ACT_FightPawnStateActions = MakeShareable(new FightPawnStateActions);
		AssetTools.RegisterAssetTypeActions(ACT_FightPawnStateActions);

		TSharedRef<IAssetTypeActions> ACT_StateChangeComponentActions = MakeShareable(new StateChangeComponentActions);
		AssetTools.RegisterAssetTypeActions(ACT_StateChangeComponentActions);
	}


	StyleSet = MakeShareable(new FSlateStyleSet("FightanProject"));

	//Content path of this plugin
	//FString ContentDir = IPluginManager::Get().FindPlugin("FightanProject")->GetBaseDir();
	FString ContentDir = IPluginManager::Get().FindPlugin("FightanProject")->GetBaseDir();

	//The image we wish to load is located inside the Resources folder inside the Base Directory
	//so let's set the content dir to the base dir and manually switch to the Resources folder:
	StyleSet->SetContentRoot(ContentDir);

	//Create a brush from the icon
	FSlateImageBrush* FightPawnStateThumbnailBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("Resources/FightPawnStateIcon"), TEXT(".png")), FVector2D(128.f, 128.f));
	FSlateImageBrush* InputSequenceBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("Resources/InputSequenceIcon"), TEXT(".png")), FVector2D(128.f, 128.f));
	FSlateImageBrush* StateChangeBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("Resources/StateChangeIcon"), TEXT(".png")), FVector2D(128.f, 128.f));

	if (FightPawnStateThumbnailBrush)
		//In order to bind the thumbnail to our class we need to type ClassThumbnail.X where X is the name of the C++ class of the asset
		StyleSet->Set("ClassThumbnail.FightPawnState", FightPawnStateThumbnailBrush);

	if (InputSequenceBrush)
		StyleSet->Set("ClassThumbnail.InputSequence", InputSequenceBrush);

	if (StateChangeBrush)
		StyleSet->Set("ClassThumbnail.StateChangeComponent", StateChangeBrush);
		
	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet);
}

void FFightanProjectEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	FSlateStyleRegistry::UnRegisterSlateStyle(StyleSet->GetStyleSetName());
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FFightanProjectEditorModule, FightanProjectEditor)