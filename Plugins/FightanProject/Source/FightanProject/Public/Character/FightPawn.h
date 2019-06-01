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

	//Input buffer that listens to the pawn's player controller
	UPROPERTY(VisibleAnywhere)
		UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere)
		float TimeInState;

	//Counter that keeps track of the behavior instruction we need to check for execution
	UPROPERTY(EditAnywhere)
		int StateInstructionCounter;

	//Counter that keeps track of the box instruction we need to check for execution
	UPROPERTY(EditAnywhere)
		int BoxInstructionCounter;

	UPROPERTY(EditAnywhere)
		float HitStopTimer;
	UPROPERTY(EditAnywhere)
		float PreviousHitStopTime;

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

	FOnIsHit OnIsHit;
	FOnHasHit OnHasHit;

	FOnHitStopEnd OnHitStopEnd;

	UFUNCTION()
		void SetHitStop(float time);

	UFUNCTION()
		void DecreaseHitStopTimer(float deltaTime);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void BroadCastOnIsHit(FHitBoxParams& HitParams);

	UFUNCTION()
		void BroadCastOnHasHit(FHitBoxParams& HitParams);

	UFUNCTION()
		void AttachSceneComponent(USceneComponent* Subject, USceneComponent* DuctTape);

	UPROPERTY()
		UFightanProjectGameInstance* GameInstance;

	UFUNCTION(BlueprintCallable)
		float GetStateTimer() const;

	UFUNCTION(BlueprintCallable)
		UCharacterStatsComponent* GetCharacterStatsComponent() const;

	UFUNCTION(BlueprintCallable)
		UFGPhysicsComponent* GetPhysicsComponent() const;

	UFUNCTION(BlueprintCallable)
		UAudioComponent* GetAudioComponent() const;

	UFUNCTION(BlueprintCallable)
		UCharacterStatsComponent* GetStatsComponent() const;

	UFUNCTION(BlueprintCallable)
		UEventStateChangeComponent* GetEventStateChangeComponent() const;

	UFUNCTION(BlueprintCallable)
		UBoxDataHandlerComponent* GetBoxDataHandlerComponent() const;

	UFUNCTION(BlueprintCallable)
		float GetHitStopTime() const;
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

FORCEINLINE UAudioComponent* AFightPawn::GetAudioComponent() const
{
	return AudioComponent;
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