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

	TimeInState = 0;
	StateInstructionCounter = 0;
}

// Called when the game starts or when spawned
void AFightPawn::BeginPlay()
{
	Super::BeginPlay();

	SwitchState(CurrentState);

	if (UFightanProjectGameInstance* gameInstance = Cast<UFightanProjectGameInstance>(GetGameInstance()))
		GameInstance = gameInstance;

	if (AFightanProjectGameModeBase* gameMode = Cast<AFightanProjectGameModeBase>(GetWorld()->GetAuthGameMode()))
		GameMode = gameMode;

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
		PhysicsComponent->UpdateComponent(DeltaTime);
		BoxDataHandler->UpdateComponent(DeltaTime);
		ExecuteTickInstructions();
	}
	else
	{
		DoHitRumble();
	}


	PreviousHitStopTime = HitStopTimer;
}

void AFightPawn::BroadCastOnIsHit(FHitBoxParams& HitParams, AFightPawn* initPawn)
{
	OnIsHit.Broadcast(HitParams);

	if (initPawn->IsFlipped() == bIsFlipped)
		FlipCharacter();

	FVector knockBackVelocity = HitParams.GroundKnockBackVelocity;
	if (initPawn->IsFlipped())
		knockBackVelocity.X = -knockBackVelocity.X;
	PhysicsComponent->SetVelocity(knockBackVelocity);

	SwitchState(PainState);
	SetHitStop(HitParams.HitStop.Y);
	HitRumbleIntensity = HitParams.HitRumbleIntensity;
	HitRumbleSpeed = HitParams.HitRumbleSpeed;
}

void AFightPawn::BroadCastOnHasHit(FHitBoxParams& HitParams, AFightPawn* hitPawn)
{
	OnHasHit.Broadcast(HitParams);

	ExecuteInstructions(HitParams.HitInstrucion);
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
						//We need to make edits to the position of the box without editing the reference that is why we copy it
						FBoxParams params = box.BoxParams;
						if (bIsFlipped)
							params.Position.X = -params.Position.X;

						switch (box.Type)
						{
						case BoxType::HIT_BOX:

							BoxDataHandler->ActivateHitBox(params, box.HitParams);
							break;

						case BoxType::HURT_BOX:

							BoxDataHandler->ActivateHurtBox(params);
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
	Flipbook->PlayFromStart();
	ExecuteTickInstructions();
}

void AFightPawn::SetHitStop(float Time)
{
	HitStopTimer = Time;
	Flipbook->Stop();
}

void AFightPawn::DecreaseHitStopTimer(float deltaTime)
{
	HitStopTimer -= deltaTime;

	if (HitStopTimer <= 0)
	{
		OnHitStopEnd.Broadcast();
		Flipbook->SetRelativeLocation(FVector::ZeroVector);
	}
}

void AFightPawn::DoHitRumble()
{
	float rumblePosition = FMath::Sin(UKismetSystemLibrary::GetGameTimeInSeconds(this) * HitRumbleSpeed) * HitRumbleIntensity;
	Flipbook->SetRelativeLocation(FVector(rumblePosition, 0, 0));
}

void AFightPawn::FlipCharacter()
{
	bIsFlipped ^= true;
	Flipbook->AddLocalRotation(FRotator(0, 180, 0));
}

void AFightPawn::AttachSceneComponent(USceneComponent* Subject, USceneComponent* DuctTape)
{
	Subject->AttachToComponent(DuctTape, FAttachmentTransformRules::KeepRelativeTransform);
}

void AFightPawn::SetVelocity(FVector velocityVector)
{
	if (bIsFlipped)
		velocityVector.X = -velocityVector.X;

	PhysicsComponent->SetVelocity(velocityVector);
}

void AFightPawn::SetVelocityX(float value)
{
	if (bIsFlipped)
		value = -value;

	PhysicsComponent->SetVelocityX(value);
}

void AFightPawn::SetVelocityZ(float value)
{
	PhysicsComponent->SetVelocityZ(value);
}

void AFightPawn::AddVelocity(FVector velocityVector)
{
	if (bIsFlipped)
		velocityVector.X = -velocityVector.X;

	PhysicsComponent->AddVelocity(velocityVector);
}

void AFightPawn::AddVelocityX(float value)
{
	if (bIsFlipped)
		value = -value;

	PhysicsComponent->AddVelocityX(value);
}

void AFightPawn::AddVelocityZ(float value)
{
	PhysicsComponent->AddVelocityZ(value);
}

void AFightPawn::SetGroundFlag(bool value)
{
	bIsGrounded = value;
}

void AFightPawn::PlaySound(USoundWave* sound)
{
	GameMode->GetManagerContainer()->GetSFXManager()->ActivateAudioComponent(sound, Container->GetComponentLocation());
}

void AFightPawn::SpawnParticle(UParticleSystem* particle, FVector position)
{
	if (bIsFlipped)
		position.X = -position.X;

	GameMode->GetManagerContainer()->GetVFXManager()->ActivateParticleSystemComponent(particle, position + Container->GetComponentLocation(), FRotator::ZeroRotator, FVector::ZeroVector);
}
