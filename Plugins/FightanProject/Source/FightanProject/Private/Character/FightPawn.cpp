// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/FightPawn.h"
#include "StateMachine/FightPawnState.h"
#include "StateMachine/EventStateChangeComponent.h"
#include "StateMachine/StateMachineResults.h"
#include "StateMachine/Instructions/StateInstructionBase.h"
#include "GameData/Box/BoxInstruction.h"
#include "Engine/DataTable.h"
#include "Game/FightanProjectGameModeBase.h"


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

	BoxDataHandler = CreateDefaultSubobject<UBoxDataHandlerComponent>(TEXT("BoxHitHurt"));
	BoxDataHandler->SetupAttachment(Container);
	BoxDataHandler->SetOwningPawn(this);

	//Pass pointer to PhysicsComponent
	PhysicsComponent->SetPushBox(PushBox);
	PhysicsComponent->SetContainer(Container);
	PhysicsComponent->SetOwningPawn(this);

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

	//EventState subscriptions
	if (PhysicsComponent != nullptr)
	{
		PhysicsComponent->OnPhysicsEvent.AddDynamic(this, &AFightPawn::CheckEventStates);
	}

	if (AFightanProjectGameModeBase* gameMode = Cast<AFightanProjectGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		gameMode->GetHitManager()->RegisterPawn(this);
	}

}

// Called every frame
void AFightPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DecreaseHitStopTimer(DeltaTime);
	if (PreviousHitStopTime > 0 && HitStopTimer <= 0)
	{
		Flipbook->Play();
		OnHitStopEnd.Broadcast();
	}

	if (HitStopTimer <= 0)
	{
		TimeInState += DeltaTime;
		CheckOnFinishState();
		ExecuteTickInstructions();
		BoxDataHandler->UpdateComponent(DeltaTime);
	}


	PreviousHitStopTime = HitStopTimer;

}


void AFightPawn::BroadCastOnIsHit(FHitBoxParams& HitParams)
{
	OnIsHit.Broadcast(HitParams);
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Emerald, TEXT("HURT!!!"));
	SetHitStop(HitParams.HitStop.Y);
}

void AFightPawn::BroadCastOnHasHit(FHitBoxParams& HitParams)
{
	OnHasHit.Broadcast(HitParams);
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Emerald, TEXT("HIT!!!"));
	SetHitStop(HitParams.HitStop.X);
}

void AFightPawn::ExecuteTickInstructions()
{
	if (CurrentState != nullptr &&  CurrentState->StateBehaviour != nullptr)
	{
		ExecuteInstructions(CurrentState->StateBehaviour->LoopInstructions);

		if (CurrentState->StateBehaviour->TickInstructionTables != nullptr)
		{
			static const FString ContextString(TEXT("Instruction Context Not Found"));
			FString IndexString = FString::FromInt(StateInstructionCounter);
			FName IndexName = FName(*IndexString);
			FInstructionRow* instructionRow = CurrentState->StateBehaviour->TickInstructionTables->FindRow<FInstructionRow>(IndexName, ContextString, false);

			if (instructionRow)
			{
				if (TimeInState >= instructionRow->Time)
				{
					ExecuteInstructions(instructionRow->Instructions);
					StateInstructionCounter++;
				}
			}
		}

		if (CurrentState->StateBehaviour->BoxInstructionTables != nullptr)
		{
			static const FString ContextString(TEXT("Instruction Context Not Found"));
			FString IndexString = FString::FromInt(BoxInstructionCounter);
			FName IndexName = FName(*IndexString);
			FBoxInstructionRow* BoxInstructionRow = CurrentState->StateBehaviour->BoxInstructionTables->FindRow<FBoxInstructionRow>(IndexName, ContextString, false);

			if (BoxInstructionRow)
			{
				if (TimeInState >= BoxInstructionRow->Time)
				{
					for (FBoxData& box : BoxInstructionRow->FrameBoxes)
					{

						switch (box.Type)
						{
						case BoxType::HIT_BOX:

							BoxDataHandler->ActivateHitBox(box.BoxParams, box.HitParams);
							break;

						case BoxType::HURT_BOX:

							BoxDataHandler->ActivateHurtBox(box.BoxParams);
							break;
						}

					}
					BoxInstructionCounter++;
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

	for (int i = 0; i < EventStateChangeComponent->EventStates.Num(); i++)
	{
		if (event == EventStateChangeComponent->EventStates[i].Event && EventStateChangeComponent->EventStates[i].EventState != nullptr)
		{
			SwitchState(EventStateChangeComponent->EventStates[i].EventState);
			CheckStateLinks(InputBufferComponent);
			break;
		}
	}
}

void AFightPawn::CheckOnFinishState()
{
	if (CurrentState->StateChangeComponent == nullptr)
		return;
	if (CurrentState->StateChangeComponent->OnFinishState.NextState == nullptr)
		return;

	if (TimeInState >= CurrentState->StateChangeComponent->OnFinishState.Time)
	{
		SwitchState(CurrentState->StateChangeComponent->OnFinishState.NextState);
		CheckStateLinks(InputBufferComponent);
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
	if (CurrentState->StateBehaviour != nullptr)
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

	//Reset box instruction counter
	BoxInstructionCounter = 0;

	BoxDataHandler->DeactivateAllActiveBoxes();

	Flipbook->SetLooping(CurrentState->bLoops);
	Flipbook->Play();
}

void AFightPawn::SetHitStop(float Time)
{
	HitStopTimer = Time;
	Flipbook->Stop();
}

void AFightPawn::DecreaseHitStopTimer(float deltaTime)
{
	HitStopTimer -= deltaTime;
}

void AFightPawn::AttachSceneComponent(USceneComponent* Subject, USceneComponent* DuctTape)
{
	Subject->AttachToComponent(DuctTape, FAttachmentTransformRules::KeepRelativeTransform);
}