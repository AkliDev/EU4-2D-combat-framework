// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/InputBuffer/InputBufferComponent.h"

// Sets default values for this component's properties
UInputBufferComponent::UInputBufferComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	//Sets default buffer size
	BufferSize = 20;

	BufferLockState = EBufferLockState::EmptyLocked;
}

// Called when the game starts
void UInputBufferComponent::BeginPlay()
{
	Super::BeginPlay();

	//Get ref to owning pawn's player controller. If it is not AFightPlayerController the CRASH or something
	if (APawn* const pawn = Cast<APawn>(GetOwner()))
	{
		if (AFightPlayerController* const playerController = Cast<AFightPlayerController>(pawn->GetController()))
		{
			PlayerController = playerController;
			PlayerController->NewInput.AddDynamic(this, &UInputBufferComponent::SetCurrentInput);
		}
	}
	else
	{
		//TODO Throw out assert error
	}

	//Create and initialize Current input class
	CurrentInput = NewObject<UBufferInputItem>();
	CurrentInput->Init((uint32)CardinalDirection::NUM + (uint32)Button::NUM);

	//Create and initialize Current input classes. These together are the Input buffer
	for (uint32 i = 0; i < BufferSize; i++)
	{
		InputBuffer.Add(NewObject<UBufferInputItem>());
		InputBuffer[i]->Init((uint32)CardinalDirection::NUM + (uint32)Button::NUM);
	}
}

void UInputBufferComponent::SetCurrentInput(uint32 inputBitflag)
{
	CurrentInpitBitflag = inputBitflag;
}

void UInputBufferComponent::AddInputBuffer()
{
	switch (BufferLockState)
	{
	case  EBufferLockState::MotionLocked:
		if (CurrentInput->DirectionAtom.Direction == DirectionNotation::NEUTRAL)
			BufferLockState = EBufferLockState::EmptyLocked;
		if (CurrentInput->DirectionAtom.Direction != DirectionNotation::NEUTRAL)
			BufferLockState = EBufferLockState::TapLocked;
		break;
	case  EBufferLockState::EmptyLocked:
		if (CurrentInput->DirectionAtom.Direction != DirectionNotation::NEUTRAL)
			BufferLockState = EBufferLockState::TapLocked;
		break;
	case  EBufferLockState::TapLocked:
		BufferLockState = EBufferLockState::Unlocked;
		break;
	case  EBufferLockState::Unlocked:
		break;
	}

	//First we shift down all input to make room at the top. UE4 Should take care of the last pointer in the Array. IF NOT I SHALL FIX THIS MEMORY LEAK
	for (uint32 i = InputBuffer.Num() - 1; i >= 1; i--)
	{
		//Assign Input stamp to the one above it
		*InputBuffer[i] = InputBuffer[i - 1];
	}

	//Add Current input to the buffer
	*InputBuffer[0] = CurrentInput;

	//Set Begin time of 1st stamp in the buffer
	InputBuffer[0]->BeginTimeStamp = UKismetSystemLibrary::GetGameTimeInSeconds(this);

	//Set End time of 2nd stamp in the buffer
	InputBuffer[1]->EndTimeStamp = UKismetSystemLibrary::GetGameTimeInSeconds(this);

	BufferItemAdd.Broadcast(this);
	UpdateBufferDisplay.Broadcast(InputBuffer);
}

// Called every frame
void UInputBufferComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	CurrentInput->UpdateInputItem(CurrentInpitBitflag, PreviousInpitBitflag, DeltaTime);
	if (PreviousInpitBitflag != CurrentInpitBitflag)
	{
		AddInputBuffer();
	}

	//Set Previous input bitflag. TODO This should probably be it's own method
	PreviousInpitBitflag = CurrentInpitBitflag;
}