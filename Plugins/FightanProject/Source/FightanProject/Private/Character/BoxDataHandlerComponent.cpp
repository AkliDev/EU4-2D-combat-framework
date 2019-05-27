// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/BoxDataHandlerComponent.h"
#include "Character/FightPawn.h"

// Sets default values for this component's properties
UBoxDataHandlerComponent::UBoxDataHandlerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	HitBoxPoolSize = 5;
	HurtBoxPoolSize = 5;
	BoxPool.SetNum(0);
}


// Called when the game starts
void UBoxDataHandlerComponent::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < HitBoxPoolSize; i++)
	{
		BoxPool.Add(CreateHitBox());
	}

	for (int i = 0; i < HurtBoxPoolSize; i++)
	{
		BoxPool.Add(CreateHurtBox());
	}
}

// Called every frame
void UBoxDataHandlerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	TArray<UTraceBox*> deadBoxes;

	for (UTraceBox* box : ActiveBoxes)
	{
		box->LifeTime -= DeltaTime;

		if (box->LifeTime <= 0)
		{
			box->Deactivate();
			deadBoxes.Add(box);
		}
	}

	for (UTraceBox* deadBox : deadBoxes)
	{
		ActiveBoxes.Remove(deadBox);
	}
}

UHitBox* UBoxDataHandlerComponent::ActivateHitBox(FBoxParams& params)
{
	//search in the pool for a hitbox that we can use. If one is found we call init on it and return it
	for (UTraceBox* box : BoxPool)
	{
		if (box->IsA(UHitBox::StaticClass()) && box->bInUse == false)
		{
			box->Init(params);
			ActiveBoxes.Add(box);
			return Cast<UHitBox>(box);
		}
	}

	//if all boxes are in use the increase the amount of hit boxes in the pool
	for (int i = 0; i < HitBoxPoolSize; i++)
	{
		BoxPool.Add(CreateHitBox());
	}

	//After we increased the amount of boxes we search for one again and return it. 
	return ActivateHitBox(params);
}

UHurtBox* UBoxDataHandlerComponent::ActivateHurtBox(FBoxParams& params)
{
	//search in the pool for a hurtbox that we can use. If one is found we call init on it and return it
	for (UTraceBox* box : BoxPool)
	{
		if (box->IsA(UHurtBox::StaticClass()) && box->bInUse == false)
		{
			box->Init(params);
			ActiveBoxes.Add(box);
			return Cast<UHurtBox>(box);
		}
	}

	//if all boxes are in use the increase the amount of hurt boxes in the pool
	for (int i = 0; i < HurtBoxPoolSize; i++)
	{
		BoxPool.Add(CreateHurtBox());
	}

	//After we increased the amount of boxes we search for one again and return it. 
	return ActivateHurtBox(params);
}

UTraceBox* UBoxDataHandlerComponent::CreateTraceBox()
{
	UTraceBox* pComponent = NewObject<UTraceBox>(this);
	pComponent->RegisterComponent();
	OwningPawns->AttachSceneComponent(pComponent, this);
	return pComponent;
}

UHitBox* UBoxDataHandlerComponent::CreateHitBox()
{
	UHitBox* pComponent = NewObject<UHitBox>(this);
	pComponent->RegisterComponent();
	OwningPawns->AttachSceneComponent(pComponent, this);
	return pComponent;
}

UHurtBox* UBoxDataHandlerComponent::CreateHurtBox()
{
	UHurtBox* pComponent = NewObject<UHurtBox>(this);
	pComponent->RegisterComponent();
	OwningPawns->AttachSceneComponent(pComponent, this);
	return pComponent;
}

void UBoxDataHandlerComponent::DeactivateAllActiveBoxes()
{
	for (UTraceBox* box : ActiveBoxes)
	{
		box->Deactivate();		
	}
	ActiveBoxes.Empty();
}

void UBoxDataHandlerComponent::SetOwningPawn(AFightPawn* owningPawn)
{
	OwningPawns = owningPawn;
}