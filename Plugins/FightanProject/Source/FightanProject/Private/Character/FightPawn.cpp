// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/FightPawn.h"
#include "StateMachine/FightPawnState.h"
#include "StateMachine/EventStateChangeComponent.h"
#include "StateMachine/StateMachineResults.h"
#include "StateMachine/Instructions/StateInstructionBase.h"
#include "Engine/DataTable.h"


// Sets default values
AFightPawn::AFightPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create InputBufferComponent for this pawn;
	InputBufferComponent = CreateDefaultSubobject<UInputBufferComponent>(TEXT("InputBufferComponent"));

	EventStateChangeComponent = CreateDefaultSubobject<UEventStateChangeComponent>(TEXT("EventStateChanges"));

	//Create Physics component for the pawn
	PhysicsComponent = CreateDefaultSubobject<UFGPhysicsComponent>(TEXT("PhysicsComponent"));
	RootComponent = PhysicsComponent;
	
	//Create PushBox
	PushBox = CreateDefaultSubobject<UPushBoxComponent>(TEXT("PushBox"));
	PushBox->SetupAttachment(RootComponent);

	Container = CreateDefaultSubobject<UCharacterContainer>(TEXT("Container"));
	Container->SetupAttachment(RootComponent);

	//Pass pointer to PhysicsComponent
	PhysicsComponent->SetPushBox(PushBox);
	PhysicsComponent->SetContainer(Container);

	//Create FlipbookComponent 
	Flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Skin"));
	Flipbook->SetupAttachment(Container);

	//Create AudioComponent
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);

	TimeInState = 0;
	StateInstructionCounter = 0;
}

// Called when the game starts or when spawned
void AFightPawn::BeginPlay()
{
	Super::BeginPlay();

	if (UFightanProjectGameInstance* gameInstance = Cast<UFightanProjectGameInstance>(GetGameInstance()))
	{
		GameInstance = gameInstance;
	}

	if (InputBufferComponent != nullptr)
		InputBufferComponent->BufferItemAdd.AddDynamic(this, &AFightPawn::CheckStateLinks);

	if (Flipbook != nullptr)
	{
		if (CurrentState != nullptr)
			Flipbook->SetFlipbook(CurrentState->Animation);

		Flipbook->OnFinishedPlaying.AddDynamic(this, &AFightPawn::SwitchToFinishState);
	}

	if (CurrentState->StateBehaviour != nullptr)
		//execute states enter instructions
		ExecuteInstructions(CurrentState->StateBehaviour->OnEnterInstructions);

	if (PhysicsComponent != nullptr)
	{
		PhysicsComponent->OnCollisionUp.AddDynamic(this, &AFightPawn::CheckEventStates);
		PhysicsComponent->OnCollisionDown.AddDynamic(this, &AFightPawn::CheckEventStates);
		PhysicsComponent->OnCollisionBehind.AddDynamic(this, &AFightPawn::CheckEventStates);
		PhysicsComponent->OnCollisionFront.AddDynamic(this, &AFightPawn::CheckEventStates);

		PhysicsComponent->OnVelpcityFlipX.AddDynamic(this, &AFightPawn::CheckEventStates);
		PhysicsComponent->OnVelpcityFlipZ.AddDynamic(this, &AFightPawn::CheckEventStates);
	}
}

// Called every frame
void AFightPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RetriveInstructionsFromInstructionTable();
	TimeInState += DeltaTime;
}

void AFightPawn::RetriveInstructionsFromInstructionTable()
{
	if (CurrentState != nullptr &&  CurrentState->StateBehaviour != nullptr)
	{
		ExecuteInstructions(CurrentState->StateBehaviour->LoopInstructions);

		if (CurrentState->StateBehaviour->TickInstructionTables != nullptr)
		{
			static const FString ContextString(TEXT("State Instruction Context Not Found"));
			FString IndexString = FString::FromInt(StateInstructionCounter);
			FName IndexName = FName(*IndexString);
			FInstructionRow* instructionRow = CurrentState->StateBehaviour->TickInstructionTables->FindRow<FInstructionRow>(IndexName, ContextString, false);

			if (instructionRow)
			{
				if (TimeInState >= instructionRow->Time)
				{
					for (int i = 0; i < instructionRow->Instructions.Num(); i++)
					{
						if (instructionRow->Instructions[i].Instruction != nullptr)
						{
							instructionRow->Instructions[i].Instruction->GetDefaultObject<UStateInstructionBase>()->Execute(this, instructionRow->Instructions[i].Params);

						}
					}
					StateInstructionCounter++;
				}
			}
		}
	}
}

void AFightPawn::ExecuteInstructions(TArray<FInstruction>& instructions)
{
	for (FInstruction& instruction : instructions)
		if (instruction.Instruction != nullptr)
			instruction.Instruction->GetDefaultObject<UStateInstructionBase>()->Execute(this, instruction.Params);
}

/// <summary>Checks if pawn needs to switch state depending on input in the given inputBuffer</summary>
/// <param name="sel">InputBufferComponent to validate when checking for conditions for links</param>  
/// <returns>void</returns>  
void AFightPawn::CheckStateLinks(const UInputBufferComponent* BufferComponent)
{
	FStateMachineResult result;

	result = CurrentState->TryLinks(this, BufferComponent);

	if (result.DestinationState != nullptr)
	{
		SwitchState(result.DestinationState);

		if (result.InputValidationResult.bMotionLock)
			InputBufferComponent->BufferLockState = EBufferLockState::MotionLocked;
	}
}

void AFightPawn::CheckEventStates(Events event)
{
	if (EventStateChangeComponent == nullptr)
		return;

	for (FEventState& state : EventStateChangeComponent->EventStates)
	{
		if (event == state.Event)
		{
			SwitchState(state.EventState);
		}
	}
}

/// <summary>Switches the current state of the pawn with the given state</summary>
/// <param name="sel">Pointer to state to switch to</param>  
void AFightPawn::SwitchState(UFightPawnState* DestinationState)
{
	if (DestinationState == nullptr)
		return;

	EventStateChangeComponent->ClearAll();

	//execute states exit instructions
	if(CurrentState->StateBehaviour != nullptr)
	ExecuteInstructions(CurrentState->StateBehaviour->OnExitInstructions);

	//switch to destination state
	CurrentState = DestinationState;

	if (CurrentState->StateBehaviour != nullptr)
	//execute states enter instructions
	ExecuteInstructions(CurrentState->StateBehaviour->OnEnterInstructions);

	//Update animation
	Flipbook->SetFlipbook(CurrentState->Animation);

	//Reset state Timer
	TimeInState = 0;

	//Reset state instruction counter
	StateInstructionCounter = 0;

	//Temporary
	if (CurrentState->StateChangeComponent != nullptr && CurrentState->StateChangeComponent->OnFinishState != nullptr)
		Flipbook->SetLooping(false);
	else
		Flipbook->SetLooping(true);

	Flipbook->Play();
}

/// <summary>When called switched pawns state to the current state's on finish state</summary> 
void AFightPawn::SwitchToFinishState()
{
	if (CurrentState->StateChangeComponent != nullptr && CurrentState->StateChangeComponent->OnFinishState != nullptr)
	{
		SwitchState(CurrentState->StateChangeComponent->OnFinishState);
		CheckStateLinks(InputBufferComponent);
	}
}