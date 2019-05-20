#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "Templates/SharedPointer.h"
#include "FightanProjectEditor.h"
 
#include "GameData/Box/BoxFrameData.h"

class ISlateStyle;

class BoxFrameDataActions : public FAssetTypeActions_Base
{
public:
	BoxFrameDataActions(const TSharedRef<ISlateStyle>& InStyle);

	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_BoxFrameData", "Box Frame Data"); }
	virtual uint32 GetCategories() override { return MY_AssetCategory; }
	virtual FColor GetTypeColor() const override { return FColor(127, 255, 255); }
	virtual FText GetAssetDescription(const FAssetData &AssetData) const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_BoxData", "Box Frame Data"); }
	virtual UClass* GetSupportedClass() const override { return UBoxFrameData::StaticClass(); }

	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;

private:

	/** Pointer to the style set to use for toolkits. */
	TSharedRef<ISlateStyle> Style;
};
 