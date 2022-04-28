// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/FightPlayerController.h"


void AFightPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("UpButton", IE_Pressed, this, &AFightPlayerController::UpPressed);
	InputComponent->BindAction("UpButton", IE_Released, this, &AFightPlayerController::UpReleased);

	InputComponent->BindAction("DownButton", IE_Pressed, this, &AFightPlayerController::DownPressed);
	InputComponent->BindAction("DownButton", IE_Released, this, &AFightPlayerController::DownReleased);

	InputComponent->BindAction("LeftButton", IE_Pressed, this, &AFightPlayerController::LeftPressed);
	InputComponent->BindAction("LeftButton", IE_Released, this, &AFightPlayerController::LeftReleased);

	InputComponent->BindAction("RightButton", IE_Pressed, this, &AFightPlayerController::RightPressed);
	InputComponent->BindAction("RightButton", IE_Released, this, &AFightPlayerController::RightReleased);

	InputComponent->BindAction("Button1", IE_Pressed, this, &AFightPlayerController::Button1Pressed);
	InputComponent->BindAction("Button1", IE_Released, this, &AFightPlayerController::Button1Released);

	InputComponent->BindAction("Button2", IE_Pressed, this, &AFightPlayerController::Button2Pressed);
	InputComponent->BindAction("Button2", IE_Released, this, &AFightPlayerController::Button2Released);

	InputComponent->BindAction("Button3", IE_Pressed, this, &AFightPlayerController::Button3Pressed);
	InputComponent->BindAction("Button3", IE_Released, this, &AFightPlayerController::Button3Released);

	InputComponent->BindAction("Button4", IE_Pressed, this, &AFightPlayerController::Button4Pressed);
	InputComponent->BindAction("Button4", IE_Released, this, &AFightPlayerController::Button4Released);

	InputComponent->BindAction("Button5", IE_Pressed, this, &AFightPlayerController::Button5Pressed);
	InputComponent->BindAction("Button5", IE_Released, this, &AFightPlayerController::Button5Released);

	InputComponent->BindAction("Button6", IE_Pressed, this, &AFightPlayerController::Button6Pressed);
	InputComponent->BindAction("Button6", IE_Released, this, &AFightPlayerController::Button6Released);
}


void AFightPlayerController::UpPressed()
{
	ControllerBitFlag |= (1 << (32 - (int32)CardinalDirection::NUM + (int32)CardinalDirection::UP));
	NewInput.Broadcast(ControllerBitFlag);
}

void AFightPlayerController::UpReleased()
{
	ControllerBitFlag &= ~(1 << (32 - (int32)CardinalDirection::NUM + (int32)CardinalDirection::UP));
	NewInput.Broadcast(ControllerBitFlag);
}

void AFightPlayerController::DownPressed()
{
	ControllerBitFlag |= (1 << (32 - (int32)CardinalDirection::NUM + (int32)CardinalDirection::DOWN));
	NewInput.Broadcast(ControllerBitFlag);
}

void AFightPlayerController::DownReleased()
{
	ControllerBitFlag &= ~(1 << (32 - (int32)CardinalDirection::NUM + (int32)CardinalDirection::DOWN));
	NewInput.Broadcast(ControllerBitFlag);
}

void AFightPlayerController::LeftPressed()
{
	ControllerBitFlag |= (1 << (32 - (int32)CardinalDirection::NUM + (int32)CardinalDirection::LEFT));
	NewInput.Broadcast(ControllerBitFlag);
}

void AFightPlayerController::LeftReleased()
{
	ControllerBitFlag &= ~(1 << (32 - (int32)CardinalDirection::NUM + (int32)CardinalDirection::LEFT));
	NewInput.Broadcast(ControllerBitFlag);
}

void AFightPlayerController::RightPressed()
{
	ControllerBitFlag |= (1 << (32 - (int32)CardinalDirection::NUM + (int32)CardinalDirection::Right));
	NewInput.Broadcast(ControllerBitFlag);
}

void AFightPlayerController::RightReleased()
{
	ControllerBitFlag &= ~(1 << (32 - (int32)CardinalDirection::NUM + (int32)CardinalDirection::Right));
	NewInput.Broadcast(ControllerBitFlag);
}

void AFightPlayerController::Button1Pressed()
{
	ControllerBitFlag |= (1 << (int32)FaceButton::BUTTON1);
	NewInput.Broadcast(ControllerBitFlag);
}

void AFightPlayerController::Button1Released()
{
	ControllerBitFlag &= ~(1 << (int32)FaceButton::BUTTON1);
	NewInput.Broadcast(ControllerBitFlag);
}

void AFightPlayerController::Button2Pressed()
{
	ControllerBitFlag |= (1 << (int32)FaceButton::BUTTON2);
	NewInput.Broadcast(ControllerBitFlag);
}

void AFightPlayerController::Button2Released()
{
	ControllerBitFlag &= ~(1 << (int32)FaceButton::BUTTON2);
	NewInput.Broadcast(ControllerBitFlag);
}

void AFightPlayerController::Button3Pressed()
{
	ControllerBitFlag |= (1 << (int32)FaceButton::BUTTON3);
	NewInput.Broadcast(ControllerBitFlag);
}

void AFightPlayerController::Button3Released()
{
	ControllerBitFlag &= ~(1 << (int32)FaceButton::BUTTON3);
	NewInput.Broadcast(ControllerBitFlag);
}

void AFightPlayerController::Button4Pressed()
{
	ControllerBitFlag |= (1 << (int32)FaceButton::BUTTON4);
	NewInput.Broadcast(ControllerBitFlag);
}

void AFightPlayerController::Button4Released()
{
	ControllerBitFlag &= ~(1 << (int32)FaceButton::BUTTON4);
	NewInput.Broadcast(ControllerBitFlag);
}

void AFightPlayerController::Button5Pressed()
{
	ControllerBitFlag |= (1 << (int32)FaceButton::BUTTON5);
	NewInput.Broadcast(ControllerBitFlag);
}

void AFightPlayerController::Button5Released()
{
	ControllerBitFlag &= ~(1 << (int32)FaceButton::BUTTON5);
	NewInput.Broadcast(ControllerBitFlag);
}

void AFightPlayerController::Button6Pressed()
{
	ControllerBitFlag |= (1 << (int32)FaceButton::BUTTON6);
	NewInput.Broadcast(ControllerBitFlag);
}

void AFightPlayerController::Button6Released()
{
	ControllerBitFlag &= ~(1 << (int32)FaceButton::BUTTON6);
	NewInput.Broadcast(ControllerBitFlag);
}

uint32 AFightPlayerController::GetControllerBitFlag()
{
	return ControllerBitFlag;
}

