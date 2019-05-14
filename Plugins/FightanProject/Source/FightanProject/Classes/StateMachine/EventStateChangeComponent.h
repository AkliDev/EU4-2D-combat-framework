// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FightPawnState.h"
#include "Events/EventEnums.h"
#include "EventStateChangeComponent.generated.h"


USTRUCT()
struct FIGHTANPROJECT_API FEventState
{
	GENERATED_BODY()

public:
	FEventState();
	FEventState(UFightPawnState* eventState, Events event, FVector window);

	UPROPERTY(EditAnywhere)
		UFightPawnState* EventState;

	UPROPERTY(EditAnywhere)
		Events Event;

	UPROPERTY(EditAnywhere)
		FVector Window;
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FIGHTANPROJECT_API UEventStateChangeComponent : public UActorComponent
{
	GENERATED_BODY()


public:
	// Sets default values for this component's properties
	UEventStateChangeComponent();

protected:
	friend class AFightPawn;

	UPROPERTY(EditAnywhere, Category = "EventState")
		TArray<FEventState> EventStates;

	void ClearAll();

public:
	UFUNCTION(BlueprintCallable, Category = "EventState")
		void AddEventState(UFightPawnState* eventState, Events event, FVector window);
};
