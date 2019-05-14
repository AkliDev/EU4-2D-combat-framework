// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/Debug/BufferDisplayWidget.h"

/// <summary>Subscribes to a pawns buffer component to display inputs on screen</summary>
/// <param name="sel">Pointer to pawn who's buffer you want to display </param>  
/// <returns>void</returns>  
void UBufferDisplayWidget::SubscribeToBuffer(AFightPawn* pawn)
{
	InputBufferComponent = Cast<UInputBufferComponent>(pawn->GetComponentByClass(UInputBufferComponent::StaticClass()));
	if (InputBufferComponent != nullptr)
		InputBufferComponent->UpdateBufferDisplay.AddDynamic(this, &UBufferDisplayWidget::AddItemToBufferDisplay);
}

/// <summary>Adds display items to the buffer display</summary>
/// <param name="sel">Inputbuffer of an InputBufferCompoennt </param>  
/// <returns>void</returns>  
void UBufferDisplayWidget::AddItemToBufferDisplay(const TArray<UBufferInputItem*>& InputItems)
{
	if (InputItems.Num() == 0)
		return;

	if (ItemsInDisplay.Num() == 0)
	{
		for (int i = 0; i < ItemLimit; i++)
		{
			ItemsInDisplay.Add(CreateWidget<UControllerStampWidget>(this, WidgetToSpawn));
			if (InputDisplay != nullptr)
				InputDisplay->AddChildToVerticalBox(ItemsInDisplay[i]);
		}
	}

	if (ItemsInDisplay.Num() > 0)
	{
		for (int i = 0; i < ItemsInDisplay.Num(); i++)
		{
			ItemsInDisplay[i]->SetElements(InputItems[i]);
		}
	}
}