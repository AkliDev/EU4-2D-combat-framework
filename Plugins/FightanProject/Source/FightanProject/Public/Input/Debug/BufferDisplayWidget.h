// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ControllerStampWidget.h"
#include "Input/InputBuffer/BufferInputItem.h"
#include "Input/InputBuffer/InputBufferComponent.h"
#include "UMG/Public/Components/VerticalBox.h"
#include "BufferDisplayWidget.generated.h"

/**
 *
 */
UCLASS()
class FIGHTANPROJECT_API UBufferDisplayWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "ControllerStamp")
		void SubscribeToBuffer(AFightPawn* pawn);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
		int ItemLimit;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
		TSubclassOf<class UControllerStampWidget>  WidgetToSpawn;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UVerticalBox* InputDisplay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	TArray<UControllerStampWidget*> ItemsInDisplay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component References")
		UInputBufferComponent* InputBufferComponent;

	UFUNCTION()
	void AddItemToBufferDisplay(const TArray<UBufferInputItem*>& InputItems);
};
