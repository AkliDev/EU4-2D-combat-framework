// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxFrameDataEditorToolKit.h"

#include "Editor.h"
#include "EditorReimportHandler.h"
#include "EditorStyleSet.h"
#include "Editor/UnrealEd/Public/SEditorViewport.h"
#include "GameData/Box/BoxFrameData.h"
#include "UObject/NameTypes.h"
#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "FBoxFrameDataEditorToolKit"

DEFINE_LOG_CATEGORY_STATIC(LogBoxFrameDataEditor, Log, All);

/* Local constants
 *****************************************************************************/
namespace BoxFrameDataEditor
{
	static const FName AppIdentifier("BoxFrameDataEditorApp");
	static const FName TabId("BoxFrameDataEditor");
}

/* FBoxFrameDataEditorToolKit structors
 *****************************************************************************/
FBoxFrameDataEditorToolKit::FBoxFrameDataEditorToolKit(const TSharedRef<ISlateStyle>& InStyle)
	:BoxFrameData(nullptr), Style(InStyle)
{

}

FBoxFrameDataEditorToolKit::~FBoxFrameDataEditorToolKit()
{
	FReimportManager::Instance()->OnPreReimport().RemoveAll(this);
	FReimportManager::Instance()->OnPostReimport().RemoveAll(this);

	GEditor->UnregisterForUndo(this);
}

/* FBoxFrameDataEditorToolKit interface
 *****************************************************************************/
void FBoxFrameDataEditorToolKit::Initialize(UBoxFrameData* InBoxFrameData, const EToolkitMode::Type InMode, const TSharedPtr<IToolkitHost>& InToolkitHost)
{
	BoxFrameData = InBoxFrameData;

	// Support undo/redo
	BoxFrameData->SetFlags(RF_Transactional);
	GEditor->RegisterForUndo(this);

	// create tab layout
	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout("Standalone_BoxFrameDataEditor")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Vertical)
				->SetSizeCoefficient(0.66f)
				->Split
				(
					FTabManager::NewStack()
					->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
					->SetHideTabWell(true)
					->SetSizeCoefficient(0.1f)

				)
				->Split
				(
					FTabManager::NewStack()
					->AddTab(BoxFrameDataEditor::TabId, ETabState::OpenedTab)
					->SetHideTabWell(true)
					->SetSizeCoefficient(0.9f)
				)
			)
		);

	FAssetEditorToolkit::InitAssetEditor(
		InMode,
		InToolkitHost,
		BoxFrameDataEditor::AppIdentifier,
		Layout,
		true /*bCreateDefaultStandaloneMenu*/,
		true /*bCreateDefaultToolbar*/,
		InBoxFrameData
	);

	RegenerateMenusAndToolbars();
}

void FBoxFrameDataEditorToolKit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("WorkspaceMenu_BoxFrameDataEditor", "Box Frame Data Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();

	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	InTabManager->RegisterTabSpawner(BoxFrameDataEditor::TabId, FOnSpawnTab::CreateSP(this, &FBoxFrameDataEditorToolKit::HandleTabManagerSpawnTab, BoxFrameDataEditor::TabId))
		.SetDisplayName(LOCTEXT("BoxFrameDataEditorTabName", "Box Frame Data Editorr"))
		.SetGroup(WorkspaceMenuCategoryRef)
		.SetIcon(FSlateIcon(FEditorStyle::GetStyleSetName(), "LevelEditor.Tabs.Viewports"));
}

void FBoxFrameDataEditorToolKit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);

	InTabManager->UnregisterTabSpawner(BoxFrameDataEditor::TabId);
}

FText FBoxFrameDataEditorToolKit::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Box Frame Data Editor");
}

FName FBoxFrameDataEditorToolKit::GetToolkitFName() const
{
	return FName("BoxFrameDataEditor");
}

FLinearColor FBoxFrameDataEditorToolKit::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}

FString FBoxFrameDataEditorToolKit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "BoxFrameData").ToString();
}

void FBoxFrameDataEditorToolKit::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(BoxFrameData);
}

TSharedRef<SDockTab> FBoxFrameDataEditorToolKit::HandleTabManagerSpawnTab(const FSpawnTabArgs& Args, FName TabIdentifier)
{
	TSharedPtr<SWidget> TabWidget = SNullWidget::NullWidget;

	if (TabIdentifier == BoxFrameDataEditor::TabId)
	{
		TabWidget = SNew(SEditorViewport);
	}

	return SNew(SDockTab)
		.TabRole(ETabRole::PanelTab)
		[
			TabWidget.ToSharedRef()
		];
}

#undef LOCTEXT_NAMESPACE
