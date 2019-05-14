// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"

#include "BufferInputItem.h"

#include "Input/FightPlayerController.h"
#include "Input/InputEnums.h"

#include "CoreUObject/Public/UObject/UObjectGlobals.h"
#include "InputBufferComponent.generated.h"

class AFightPawn;
//Event to update the input buffer widget
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateBufferDisplay, const TArray<UBufferInputItem*>&, InputBuffer);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBufferItemAdd, const  UInputBufferComponent*, BufferComponent);

UENUM()
enum class EBufferLockState : uint8
{
	//Buffer will not be checked if the buffer state is MotionLocked because we don't check motions after we have just succeeded in doing one
	MotionLocked,
	//Buffer will not be checked if the buffer state is EmptyLocked because we don't check for motions if the previous direction was neutral
	EmptyLocked,

	TapLocked,
	//When the buffer state is Unlocked we are free to check links for valid motions
	Unlocked

};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FIGHTANPROJECT_API UInputBufferComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInputBufferComponent();

	FOnBufferItemAdd BufferItemAdd;
	FUpdateBufferDisplay UpdateBufferDisplay;

protected:

	friend class AFightPawn;

	// Called when the game starts
	virtual void BeginPlay() override;

	//Pointer to the pawns player controller
	UPROPERTY(EditAnywhere)
		AFightPlayerController* PlayerController;

	//How many input input stamps long the buffer is.
	UPROPERTY(EditAnywhere)
		uint32 BufferSize;

	//Player input of this update
	UPROPERTY(EditAnywhere)
		uint32 CurrentInpitBitflag;
	//Player input of the previous update
	UPROPERTY(EditAnywhere)
		uint32 PreviousInpitBitflag;

	//Set Current Input Bitflag
	UFUNCTION()
		void SetCurrentInput(uint32 inputBitflag);

	//Adds Current controller state to the inputbuffer
	UFUNCTION()
		void AddInputBuffer();



public:

	//Current controller state
	UPROPERTY(VisibleInstanceOnly)
		UBufferInputItem* CurrentInput;


	//The input buffer that stores controller states
	UPROPERTY(VisibleInstanceOnly)
		TArray<UBufferInputItem*> InputBuffer;

	UPROPERTY(EditAnywhere)
		EBufferLockState BufferLockState;

	UBufferInputItem* GetCurrentInput() const;
	const TArray<UBufferInputItem*>& GetInputBuffer() const;
	EBufferLockState GetBufferLockState() const;


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};

FORCEINLINE UBufferInputItem* UInputBufferComponent::GetCurrentInput() const
{
	return CurrentInput;
}

FORCEINLINE const TArray<UBufferInputItem*>& UInputBufferComponent::GetInputBuffer() const
{
	return InputBuffer;
}

FORCEINLINE EBufferLockState UInputBufferComponent::GetBufferLockState() const
{
	return BufferLockState;
}