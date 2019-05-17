// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachine/EventStateChangeComponent.h"


FEventState::FEventState()
: EventState(nullptr), Event(Events::ON_COLLISION_BEHIND), Window(FVector2D::ZeroVector) {}
FEventState::FEventState(UFightPawnState* eventState, Events event, FVector2D window)
	: EventState(eventState),  Event(event), Window(window){}

// Sets default values for this component's properties
UEventStateChangeComponent::UEventStateChangeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}

void UEventStateChangeComponent::ClearAll()
{
	EventStates.Empty();
}

void UEventStateChangeComponent::AddEventState(UFightPawnState* eventState, Events event, FVector2D window)
{
	EventStates.Add(FEventState(eventState, event, window));
}