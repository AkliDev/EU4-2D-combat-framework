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
#include "Managers/VFXManager.h"
#include "FightPawn.generated.h"


//Forward declaration to prevent circular dependency 
struct FStateMachineResult;
class UFightPawnState;
class AFightanProjectGameModeBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnIsHit, FHitBoxParams&, HitParams);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHasHit, FHitBoxParams&, HitParams);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHitStopEnd);

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

#pragma region Components

	UPROPERTY(EditAnywhere)
		UCharacterStatsComponent* Stats;

	UPROPERTY(EditAnywhere)
		UFightPawnState* CurrentState;

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
#pragma endregion

#pragma region Character Flags

	UPROPERTY(EditAnywhere)
		uint32 bIsFlipped : 1;

	UPROPERTY(EditAnywhere)
		uint32 bIsGrounded : 1;
#pragma endregion

#pragma region Counters and timers

	UPROPERTY(EditAnywhere)
		float TimeInState;

	//Counter that keeps track of the behavior instruction we need to check for execution
	UPROPERTY(EditAnywhere)
		int StateInstructionCounter;

	//Counter that keeps track of the box instruction we need to check for execution
	UPROPERTY(EditAnywhere)
		int BoxInstructionCounter;

	UPROPERTY(EditAnywhere)
		float HitStunTimer;

	UPROPERTY(EditAnywhere)
		float HitStopTimer;

	UPROPERTY(EditAnywhere)
		float PreviousHitStopTime;

	UPROPERTY(EditAnywhere)
		float HitRumbleIntensity;

	UPROPERTY(EditAnywhere)
		float HitRumbleSpeed;

#pragma endregion


#pragma region PainStates pointers

	UPROPERTY(EditAnywhere)
		UFightPawnState* PainState;

#pragma endregion 

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

	UFUNCTION()
		void SetHitStop(float time);

	UFUNCTION()
		void DecreaseHitStopTimer(float deltaTime);

	UFUNCTION()
		void DoHitRumble();

	UFUNCTION()
		void FlipCharacter();
#pragma region Events

	FOnIsHit OnIsHit;
	FOnHasHit OnHasHit;

	FOnHitStopEnd OnHitStopEnd;
#pragma endregion 



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void BroadCastOnIsHit(FHitBoxParams& HitParams, AFightPawn* initPawn);

	UFUNCTION()
		void BroadCastOnHasHit(FHitBoxParams& HitParams, AFightPawn* pawnPawn);

	UFUNCTION()
		void AttachSceneComponent(USceneComponent* Subject, USceneComponent* DuctTape);

	UPROPERTY()
		UFightanProjectGameInstance* GameInstance;

	UPROPERTY(EditAnywhere)
		AFightanProjectGameModeBase* GameMode;

#pragma region Getters
	UFUNCTION(BlueprintCallable)
		float GetStateTimer() const;

	UFUNCTION(BlueprintCallable)
		UCharacterStatsComponent* GetCharacterStatsComponent() const;

	UFUNCTION(BlueprintCallable)
		UFGPhysicsComponent* GetPhysicsComponent() const;

	UFUNCTION(BlueprintCallable)
		UCharacterStatsComponent* GetStatsComponent() const;

	UFUNCTION(BlueprintCallable)
		UEventStateChangeComponent* GetEventStateChangeComponent() const;

	UFUNCTION(BlueprintCallable)
		UBoxDataHandlerComponent* GetBoxDataHandlerComponent() const;

	UFUNCTION(BlueprintCallable)
		float GetHitStopTime() const;

	UFUNCTION(BlueprintCallable)
		bool IsFlipped() const;

	UFUNCTION(BlueprintCallable)
		bool IsGrounded() const;
#pragma endregion 

#pragma region Instruction Functions

	UFUNCTION(BlueprintCallable)
		void SetVelocity(FVector velocityVector);

	UFUNCTION(BlueprintCallable)
		void SetVelocityX(float value);

	UFUNCTION(BlueprintCallable)
		void SetVelocityZ(float value);

	UFUNCTION(BlueprintCallable)
		void AddVelocity(FVector velocityVector);

	UFUNCTION(BlueprintCallable)
		void AddVelocityX(float value);

	UFUNCTION(BlueprintCallable)
		void AddVelocityZ(float value);

	UFUNCTION(BlueprintCallable)
		void SetGroundFlag(bool value);

	UFUNCTION(BlueprintCallable)
		void PlaySound(USoundWave* sound);

	UFUNCTION(BlueprintCallable)
		void SpawnParticle(UParticleSystem* particle, FVector Position);

	

#pragma endregion 
};


FORCEINLINE float AFightPawn::GetStateTimer() const
{
	return TimeInState;
}

FORCEINLINE UCharacterStatsComponent* AFightPawn::GetCharacterStatsComponent() const
{
	return Stats;
}

FORCEINLINE UFGPhysicsComponent* AFightPawn::GetPhysicsComponent() const
{
	return PhysicsComponent;
}

FORCEINLINE UCharacterStatsComponent* AFightPawn::GetStatsComponent() const
{
	return Stats;
}

FORCEINLINE UEventStateChangeComponent* AFightPawn::GetEventStateChangeComponent() const
{
	return EventStateChangeComponent;
}

FORCEINLINE UBoxDataHandlerComponent* AFightPawn::GetBoxDataHandlerComponent() const
{
	return BoxDataHandler;
}

FORCEINLINE float AFightPawn::GetHitStopTime() const
{
	return HitStopTimer;
}

FORCEINLINE bool AFightPawn::IsFlipped() const
{
	return bIsFlipped;
}

FORCEINLINE bool AFightPawn::IsGrounded() const
{
	return bIsGrounded;
}