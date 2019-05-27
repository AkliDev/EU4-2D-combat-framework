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
#include "CharacterStatsComponent.h"
#include "BoxDataHandlerComponent.h"
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
		UCharacterStatsComponent* Stats;

	UPROPERTY(EditAnywhere)
		UFightPawnState* CurrentState;

	UPROPERTY(EditAnywhere)
		float TimeInState;

	//Counter that keeps track of the behavior instruction we need to check for execution
	UPROPERTY(EditAnywhere)
		int StateInstructionCounter;

	//Counter that keeps track of the box instruction we need to check for execution
	UPROPERTY(EditAnywhere)
		int BoxInstructionCounter;

	//Pawns physics component
	UPROPERTY(VisibleAnywhere)
		UFGPhysicsComponent* PhysicsComponent;

	//Panws pushbox
	UPROPERTY(VisibleAnywhere)
		UPushBoxComponent* PushBox;

	UPROPERTY(VisibleAnywhere)
		UBoxDataHandlerComponent* BoxDataHandler;

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

	UFUNCTION()
		void ExecuteTickInstructions();

	UFUNCTION()
		void ExecuteInstructions(TArray<FInstruction>& instructions);

	UFUNCTION()
		void CheckStateLinks(const UInputBufferComponent* BufferComponent);

	UFUNCTION()
		void CheckEventStates(Events event);

	UFUNCTION()
		void CheckOnFinishState();

	UFUNCTION(BlueprintCallable)
		void SwitchState(UFightPawnState* DestinationState);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void AttachSceneComponent(USceneComponent* Subject, USceneComponent* DuctTape);

	UPROPERTY()
		UFightanProjectGameInstance* GameInstance;
	UFUNCTION(BlueprintCallable)
		float GetStateTimer();

	UFUNCTION(BlueprintCallable)
		UCharacterStatsComponent* GetCharacterStatsComponent();

	UFUNCTION(BlueprintCallable)
		UFGPhysicsComponent* GetPhysicsComponent();

	UFUNCTION(BlueprintCallable)
		UAudioComponent* GetAudioComponent();

	UFUNCTION(BlueprintCallable)
		UCharacterStatsComponent* GetStatsComponent();

	UFUNCTION(BlueprintCallable)
		UEventStateChangeComponent* GetEventStateChangeComponent();
};


FORCEINLINE float AFightPawn::GetStateTimer()
{
	return TimeInState;
}

FORCEINLINE UCharacterStatsComponent* AFightPawn::GetCharacterStatsComponent()
{
	return Stats;
}

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
	return Stats;
}

FORCEINLINE UEventStateChangeComponent* AFightPawn::GetEventStateChangeComponent()
{
	return EventStateChangeComponent;
}