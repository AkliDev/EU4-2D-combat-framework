// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "UMG/Public/Components/TextBlock.h"
#include "UMG/Public/Components/Image.h"

#include "Input/InputBuffer/BufferInputItem.h"
#include "Input/InputBuffer/InputBufferComponent.h"
#include "Input/InputUtility.h"
#include "Input/InputEnums.h"

#include "Character/FightPawn.h"
#include "ControllerStampWidget.generated.h"

/**
 *
 */
UCLASS(Abstract, editinlinenew, BlueprintType, Blueprintable, meta = (DontUseGenericSpawnObject = "True", DisableNativeTick))
class FIGHTANPROJECT_API UControllerStampWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Id")
		int WidgetId;

	UFUNCTION(BlueprintCallable, Category = "ControllerStamp")
		void SetElements(const UBufferInputItem* InputItem);

	UFUNCTION(Category = "ControllerStamp")
		void AddButtonReferences();
	UFUNCTION(Category = "ControllerStamp")
		void AddButtonTimeReferences();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component References")
		UInputBufferComponent* InputBufferComponent;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* InputBitflagText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* BeginTimeText;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* EndTimeText;

#pragma region ButtonIconReferences
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* Button1Icon;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* Button2Icon;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* Button3Icon;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* Button4Icon;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* Button5Icon;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* Button6Icon;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* UpButtonIcon;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* DownButtonIcon;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* LeftButtonIcon;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* RightButtonIcon;

#pragma endregion

	
#pragma region ButtonTimeTextRefernces


	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Button1Time;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Button2Time;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Button3Time;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Button4Time;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Button5Time;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* Button6Time;


	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* UpButtonTime;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* DownButtonTime;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* LeftButtonTime;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* RightButtonTime;
#pragma endregion

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* DirectionIcon;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* DirectionTimeText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* ReleasedDirectionIcon;
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* ReLeasedDirectionTimeText;

	TArray<UImage*> InputIcons;
	TArray<UTextBlock*> InputTimesText;
};
