#include "BoxFrameDataActions.h"
#include "Toolkits//BoxFrameDataEditorToolKit.h"
#include "GameData/Box/BoxFrameData.h"


BoxFrameDataActions::BoxFrameDataActions(const TSharedRef<ISlateStyle>& InStyle)
	:Style(InStyle)
{

}

void BoxFrameDataActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor /*= TSharedPtr<IToolkitHost>()*/)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto ObjIt = InObjects.CreateConstIterator(); ObjIt; ++ObjIt)
	{
		auto boxFrameData = Cast<UBoxFrameData>(*ObjIt);

		if (boxFrameData != nullptr)
		{
			TSharedRef<FBoxFrameDataEditorToolKit> EditorToolkit = MakeShareable(new FBoxFrameDataEditorToolKit(Style));
			EditorToolkit->Initialize(boxFrameData, Mode, EditWithinLevelEditor);
		}
	}
}
