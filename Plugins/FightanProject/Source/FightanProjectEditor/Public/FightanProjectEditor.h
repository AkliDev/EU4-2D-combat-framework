// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

#include "AssetTypeCategories.h"
#include "SlateStyle.h"

static EAssetTypeCategories::Type MY_AssetCategory;

class FFightanProjectEditorModule : public IHasMenuExtensibility, public IHasToolBarExtensibility, public IModuleInterface
{

public:
	//~ IHasMenuExtensibility interface
	virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override;

	//~ IHasToolBarExtensibility interface
	virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override;

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void RegisterAssetTools();
	void UnregisterAssetTools();

	/** Registers main menu and tool bar menu extensions. */
	void RegisterMenuExtensions();

	/** Unregisters main menu and tool bar menu extensions. */
	void UnregisterMenuExtensions();

	void RegisterSetting();
	void UnregisterSetting();

	void RegisterSlateStyle();

private:

	/** Holds the menu extensibility manager. */
	TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;

	/** The collection of registered asset type actions. */
	TArray<TSharedRef<IAssetTypeActions>> RegisteredAssetTypeActions;

	/** Holds the plug-ins style set. */
	TSharedPtr<ISlateStyle> Style;

	TSharedPtr<FSlateStyleSet> StyleSet;

	/** Holds the tool bar extensibility manager. */
	TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;
};
