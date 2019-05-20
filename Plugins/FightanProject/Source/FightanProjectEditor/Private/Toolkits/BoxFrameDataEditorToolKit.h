// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EditorUndoClient.h"
#include "Templates/SharedPointer.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "UObject/GCObject.h"

class FSpawnTabArgs;
class ISlateStyle;
class IToolkitHost;
class SDockTab;
class UBoxFrameData;

/**
 *
 */
class FBoxFrameDataEditorToolKit : public FAssetEditorToolkit, public FEditorUndoClient, public FGCObject
{
public:
	/**
	 * Creates and initializes a new instance.
	 *
	 * @param InStyle The style set to use.
	 */
	FBoxFrameDataEditorToolKit(const TSharedRef<ISlateStyle>& InStyle);

	/** Virtual destructor. */
	virtual ~FBoxFrameDataEditorToolKit();

public:
	/**
	 * Initializes the editor tool kit.
	 *
	 * @param InTextAsset The UTextAsset asset to edit.
	 * @param InMode The mode to create the toolkit in.
	 * @param InToolkitHost The toolkit host.
	 */
	void Initialize(UBoxFrameData* InBoxFrameData, const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost);


public:

	//~ FAssetEditorToolkit interface

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager) override;

public:
	//~ FAssetEditorToolkit interface
	virtual FText GetBaseToolkitName() const override;
	virtual FName GetToolkitFName() const override;
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FString GetWorldCentricTabPrefix() const override;

	//~ FGCObject interface
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
private:

	/** Callback for spawning the Properties tab. */
	TSharedRef<SDockTab> HandleTabManagerSpawnTab(const FSpawnTabArgs& Args, FName TabIdentifier);

private:
	/** The box frame data being edited. */
	UBoxFrameData* BoxFrameData;

	/** Pointer to the style set to use for toolkits. */
	TSharedRef<ISlateStyle> Style;
};
