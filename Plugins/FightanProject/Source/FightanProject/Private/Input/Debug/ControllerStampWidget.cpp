// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/Debug/ControllerStampWidget.h"

void UControllerStampWidget::SetElements(const UBufferInputItem* InputItem)
{
	if (InputItem == nullptr)
		return;

	if (InputIcons.Num() == 0)
		AddButtonReferences();
	if (InputTimesText.Num() == 0)
		AddButtonTimeReferences();


	if (InputTimesText.Num() > 0 && InputIcons.Num() > 0)
	{
		for (int i = 0; i < InputItem->InputAtoms.Num(); i++)
		{
			if (InputTimesText[i] != nullptr)
				InputTimesText[i]->SetText(FText::FromString(FString::SanitizeFloat(InputItem->InputAtoms[i].HoldTime)));

			if (InputIcons[i] != nullptr)
			{

				switch (InputItem->InputAtoms[i].State)
				{
				case InputState::RELEASED:
					InputIcons[i]->SetColorAndOpacity(FColor::Red);
					break;
				case InputState::NOT_PRESSED:
					InputIcons[i]->SetColorAndOpacity(FColor::White);
					break;
				case InputState::PRESSED:
					InputIcons[i]->SetColorAndOpacity(FColor::Green);
					break;
				case InputState::HELD:
					InputIcons[i]->SetColorAndOpacity(FColor::Blue);
					break;
				}
			}
		}
	}

	if (DirectionIcon != nullptr)
	{
		if (InputItem->DirectionAtom.Direction == DirectionNotation::NEUTRAL)
		{
			DirectionIcon->SetColorAndOpacity(FColor(0, 0, 0, 0));
		}
		else
		{
			DirectionIcon->SetColorAndOpacity(FColor::Green);
			switch (InputItem->DirectionAtom.Direction)
			{
			case DirectionNotation::DOWN_BACK:
				DirectionIcon->SetRenderAngle(225);
				break;
			case DirectionNotation::DOWN:
				DirectionIcon->SetRenderAngle(180);
				break;
			case DirectionNotation::DOWN_FORWARD:
				DirectionIcon->SetRenderAngle(135);
				break;
			case DirectionNotation::BACK:
				DirectionIcon->SetRenderAngle(270);
				break;
			case DirectionNotation::FORWARD:
				DirectionIcon->SetRenderAngle(90);
				break;
			case DirectionNotation::UP_BACK:
				DirectionIcon->SetRenderAngle(315);
				break;
			case DirectionNotation::UP:
				DirectionIcon->SetRenderAngle(0);
				break;
			case DirectionNotation::UP_FORWARD:
				DirectionIcon->SetRenderAngle(45);
				break;
			}
		}
	}

	if (ReleasedDirectionIcon != nullptr)
	{
		if (InputItem->ReleasedDirectionAtom.Direction == DirectionNotation::NEUTRAL)
		{
			ReleasedDirectionIcon->SetColorAndOpacity(FColor(0, 0, 0, 0));
		}
		else
		{
			ReleasedDirectionIcon->SetColorAndOpacity(FColor::Red);
			switch (InputItem->ReleasedDirectionAtom.Direction)
			{
			case DirectionNotation::DOWN_BACK:
				ReleasedDirectionIcon->SetRenderAngle(225);
				break;
			case DirectionNotation::DOWN:
				ReleasedDirectionIcon->SetRenderAngle(180);
				break;
			case DirectionNotation::DOWN_FORWARD:
				ReleasedDirectionIcon->SetRenderAngle(135);
				break;
			case DirectionNotation::BACK:
				ReleasedDirectionIcon->SetRenderAngle(270);
				break;
			case DirectionNotation::FORWARD:
				ReleasedDirectionIcon->SetRenderAngle(90);
				break;
			case DirectionNotation::UP_BACK:
				ReleasedDirectionIcon->SetRenderAngle(315);
				break;
			case DirectionNotation::UP:
				ReleasedDirectionIcon->SetRenderAngle(0);
				break;
			case DirectionNotation::UP_FORWARD:
				ReleasedDirectionIcon->SetRenderAngle(45);
				break;
			}
		}
	}

	if (DirectionTimeText != nullptr)
		DirectionTimeText->SetText(FText::FromString(FString::SanitizeFloat(InputItem->DirectionAtom.HoldTime)));

	if (ReLeasedDirectionTimeText != nullptr)
		ReLeasedDirectionTimeText->SetText(FText::FromString(FString::SanitizeFloat(InputItem->ReleasedDirectionAtom.HoldTime)));

	if (InputBitflagText != nullptr)
		InputBitflagText->SetText(FText::FromString((UInputUtility::ConvertInputBitflagToBinaryString(InputItem->InputBitflag))));
	if (BeginTimeText != nullptr)
		BeginTimeText->SetText(FText::FromString(FString::SanitizeFloat(InputItem->BeginTimeStamp)));
	if (EndTimeText != nullptr)
		EndTimeText->SetText(FText::FromString(FString::SanitizeFloat(InputItem->EndTimeStamp)));
}

void UControllerStampWidget::AddButtonReferences()
{
	InputIcons.Add(Button1Icon);
	InputIcons.Add(Button2Icon);
	InputIcons.Add(Button3Icon);
	InputIcons.Add(Button4Icon);
	InputIcons.Add(Button5Icon);
	InputIcons.Add(Button6Icon);

	InputIcons.Add(UpButtonIcon);
	InputIcons.Add(DownButtonIcon);
	InputIcons.Add(LeftButtonIcon);
	InputIcons.Add(RightButtonIcon);
}

void UControllerStampWidget::AddButtonTimeReferences()
{
	InputTimesText.Add(Button1Time);
	InputTimesText.Add(Button2Time);
	InputTimesText.Add(Button3Time);
	InputTimesText.Add(Button4Time);
	InputTimesText.Add(Button5Time);
	InputTimesText.Add(Button6Time);

	InputTimesText.Add(UpButtonTime);
	InputTimesText.Add(DownButtonTime);
	InputTimesText.Add(LeftButtonTime);
	InputTimesText.Add(RightButtonTime);
}
