// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Input/InputBuffer/InputBufferComponent.h"
#include "Paper2D/Classes/PaperFlipbookComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Game/FightanProjectGameInstance.h"
#include "GameFramework/Pawn.h"
#include "Physics/FGPhysicsComponent.h"
#include "Physics/Collision/Box/PushBoxComponent.h"
#include "Character/CharacterContainer.h"
#include "Classes/Components/AudioComponent.h"
#include "Character/CharacterStatsComponent.h"
#include "StateMachine/Instructions/StateInstructionBase.h"
#include "StateMachine/Events/EventEnums.h"
#include "FightPawn.generated.h"

//Forward declaration to prevent circular dependency 
struct FStateMachineResult;
class UFightPawnState;

UCLASS()
class FIGHTANPROJECT_API AFightPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFightPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		UFightPawnState* CurrentState;

	UPROPERTY(EditAnywhere)
		float TimeInState;

	//Counter that keeps track of the instruction we need to check for execution
	UPROPERTY(EditAnywhere)
		int StateInstructionCounter;

	//Pawns physics component
	UPROPERTY(VisibleAnywhere)
		UFGPhysicsComponent* PhysicsComponent;

	//Panws pushbox
	UPROPERTY(VisibleAnywhere)
		UPushBoxComponent* PushBox;

	//Component that will contain everything but the pushbox
	UPROPERTY(VisibleAnywhere)
		UCharacterContainer* Container;

	//The current EditInstanceOnly of the pawn
	UPROPERTY(VisibleAnywhere)
		UPaperFlipbookComponent* Flipbook;

	//Input buffer that listens to the pawn's player controller
	UPROPERTY(VisibleAnywhere)
		UInputBufferComponent* InputBufferComponent;

	UPROPERTY(VisibleAnywhere)
		UEventStateChangeComponent* EventStateChangeComponent;

	//Input buffer that listens to the pawn's player controller
	UPROPERTY(VisibleAnywhere)
		UAudioComponent* AudioComponent;

	UPROPERTY(VisibleAnywhere)
		UCharacterStatsComponent* StatsComponent;

	UFUNCTION()
		void RetriveInstructionsFromInstructionTable();

	UFUNCTION()
		void ExecuteInstructions(TArray<FInstruction>& instructions);

	UFUNCTION()
		void CheckStateLinks(const UInputBufferComponent* BufferComponent);

	UFUNCTION()
		void CheckEventStates(Events event);

	UFUNCTION(BlueprintCallable)
		void SwitchState(UFightPawnState* DestinationState);

	UFUNCTION()
		void SwitchToFinishState();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
		UFightanProjectGameInstance* GameInstance;

	UFUNCTION(BlueprintCallable)
		UFGPhysicsComponent* GetPhysicsComponent();

	UFUNCTION(BlueprintCallable)
		UAudioComponent* GetAudioComponent();

	UFUNCTION(BlueprintCallable)
		UCharacterStatsComponent* GetStatsComponent();

	UFUNCTION(BlueprintCallable)
		UEventStateChangeComponent* GetEventStateChangeComponent();
};

FORCEINLINE UFGPhysicsComponent* AFightPawn::GetPhysicsComponent()
{
	return PhysicsComponent;
}

FORCEINLINE UAudioComponent* AFightPawn::GetAudioComponent()
{
	return AudioComponent;
}

FORCEINLINE UCharacterStatsComponent* AFightPawn::GetStatsComponent()
{
	return StatsComponent;
}

FORCEINLINE UEventStateChangeComponent* AFightPawn::GetEventStateChangeComponent()
{
	return EventStateChangeComponent;
}