// Fill out your copyright notice in the Description page of Project Settings.

#include "Physics/PhysicsWorld.h"

// Sets default values for this component's properties
UPhysicsWorld::UPhysicsWorld()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	MaxSolveRecursionCount = 20;
	// ...
}

// Called when the game starts
void UPhysicsWorld::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

void UPhysicsWorld::TranslatePushBoxes(float deltaTime)
{
	UpdateCurrentStateOfBoxes();

	bool didSomethingCollide = false;

	for (int i = 0; i < PhysicsEntities.Num(); i++)
	{
		if (PhysicsEntities[i] != nullptr)
			if (PhysicsEntities[i]->GetPushBox() != nullptr)
			{
				if (!PhysicsEntities[i]->GetVelocity().IsZero())
				{
					didSomethingCollide |= CheckPushPhysicsForBoxes(CurrentStateOfBoxes[i], PhysicsEntities[i]->GetVelocity() * deltaTime, PhysicsEntities[i]);
				}

				//didSomethingCollide |= CheckPushPhysicsForBoxes(CurrentStateOfBoxes[i], PhysicsEntities[i]->GetVelocity() * deltaTime, PhysicsEntities[i]);
			}
	}

	int safetyCounter = 0;

	while (didSomethingCollide)
	{
		if (safetyCounter > MaxSolveRecursionCount)
			break;

		for (int i = 0; i < PhysicsEntities.Num(); i++)
		{
			didSomethingCollide |= CheckPushPhysicsForBoxes(CurrentStateOfBoxes[i], FVector::ZeroVector, nullptr);
		}

		safetyCounter++;
	}

	for (UCastBox* box : CurrentStateOfBoxes)
	{
		box->GetBoxRef()->SetWorldLocation(box->GetPosition());
	}
}

bool UPhysicsWorld::CheckPushPhysicsForBoxes(UCastBox* castBox, FVector displacement, UFGPhysicsComponent* refComponent)
{
	castBox->AddToPosition(displacement);
	bool didBoxCollide = false;

	TArray<UPhysicsBoxComponent*> staticOverlaps = GetStaticOverlapBoxes(castBox);
	for (UPhysicsBoxComponent* other : staticOverlaps)
	{
		FOverLapData overLap = UCollisionUtility::GetBoxOverlap(castBox, other);
		castBox->AddToPosition(overLap.MTV);
		didBoxCollide = true;

		if (refComponent != nullptr)
			refComponent->FireCollisionEvents(overLap.MTV);
	}

	TArray<UCastBox*> dynamicOverlaps = GetOverlapCurrentStateOfBoxes(castBox);
	for (UCastBox* other : dynamicOverlaps)
	{
		FOverLapData overLap = UCollisionUtility::GetBoxOverlap(castBox, other);

		if (castBox->GetType() == PhysicsType::STATIC)
		{
			other->AddToPosition(FVector(-overLap.XOverLap, 0, 0));
		}
		else if (castBox->GetType() == PhysicsType::DYNAMIC)
		{
			castBox->AddToPosition(FVector(overLap.XOverLap, 0, 0) * 0.5f);
			other->AddToPosition(FVector(overLap.XOverLap, 0, 0) * -0.5f);
		}
		didBoxCollide = true;
	}

	return didBoxCollide;
}

void UPhysicsWorld::UpdateCurrentStateOfBoxes()
{
	for (UCastBox* box : CurrentStateOfBoxes)
	{
		box->Update();
	}
}

TArray<UPhysicsBoxComponent*> UPhysicsWorld::GetOverlapBoxes(UCastBox* castBox)
{
	TArray<UPhysicsBoxComponent*> Boxes;
	for (UPhysicsBoxComponent* other : PhysicsBoxes)
	{
		if (castBox->GetBoxRef() != other)
			if (UCollisionUtility::AreBoxesIntersecting(castBox, other))
				Boxes.Add(other);
	}
	return Boxes;
}

TArray<UPhysicsBoxComponent*> UPhysicsWorld::GetOverlapBoxes(UFGCollisionBoxBase* castBox)
{
	TArray<UPhysicsBoxComponent*> Boxes;

	for (UPhysicsBoxComponent* other : PhysicsBoxes)
	{
		if (castBox != other)
			if (UCollisionUtility::AreBoxesIntersecting(castBox, other))
				Boxes.Add(other);
	}
	return Boxes;
}

TArray<UPhysicsBoxComponent*> UPhysicsWorld::GetDynamicOverlapBoxes(UCastBox* castBox)
{
	TArray<UPhysicsBoxComponent*> Boxes;
	for (UFGPhysicsComponent* other : PhysicsEntities)
	{
		if (castBox->GetBoxRef() != other->GetPushBox())
			if (UCollisionUtility::AreBoxesIntersecting(castBox, other->GetPushBox()))
				Boxes.Add(other->GetPushBox());
	}
	return Boxes;
}

TArray<UPhysicsBoxComponent*> UPhysicsWorld::GetDynamicOverlapBoxes(UFGCollisionBoxBase* castBox)
{
	TArray<UPhysicsBoxComponent*> Boxes;
	for (UFGPhysicsComponent* other : PhysicsEntities)
	{
		if (castBox != other->GetPushBox())
			if (UCollisionUtility::AreBoxesIntersecting(castBox, other->GetPushBox()))
				Boxes.Add(other->GetPushBox());
	}
	return Boxes;
}

TArray<UPhysicsBoxComponent*> UPhysicsWorld::GetStaticOverlapBoxes(UCastBox* castBox)
{
	TArray<UPhysicsBoxComponent*> Boxes;
	for (UPhysicsBoxComponent* other : EnviormentCollisionBoxes)
	{
		if (castBox->GetBoxRef() != other)
			if (UCollisionUtility::AreBoxesIntersecting(castBox, other))
				Boxes.Add(other);
	}
	return Boxes;
}

TArray<UPhysicsBoxComponent*> UPhysicsWorld::GetStaticOverlapBoxes(UFGCollisionBoxBase* castBox)
{
	TArray<UPhysicsBoxComponent*> Boxes;
	for (UPhysicsBoxComponent* other : EnviormentCollisionBoxes)
	{
		if (castBox != other)
			if (UCollisionUtility::AreBoxesIntersecting(castBox, other))
				Boxes.Add(other);
	}
	return Boxes;
}

TArray<UCastBox*> UPhysicsWorld::GetOverlapCurrentStateOfBoxes(UCastBox* castBox)
{
	TArray<UCastBox*> Boxes;
	for (UCastBox* other : CurrentStateOfBoxes)
	{
		if (castBox != other)
			if (UCollisionUtility::AreBoxesIntersecting(castBox, other))
				Boxes.Add(other);
	}
	return Boxes;
}

// Called every frame
void UPhysicsWorld::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (UFGPhysicsComponent* entity : PhysicsEntities)
	{
		entity->AddGravity(DeltaTime);
	}

	TranslatePushBoxes(DeltaTime);
}

void UPhysicsWorld::RegistePhysicsComponent(UFGPhysicsComponent* physicsComponent)
{
	if (physicsComponent == nullptr || physicsComponent->GetPushBox() == nullptr)
		return;

	if (!PhysicsEntities.Contains(physicsComponent))
	{
		PhysicsEntities.Add(physicsComponent);

		UCastBox* castBox = NewObject<UCastBox>();
		castBox->Init(physicsComponent->GetPushBox());
		CurrentStateOfBoxes.Add(castBox);
	}

	if (!PhysicsBoxes.Contains(physicsComponent->GetPushBox()))
		PhysicsBoxes.Add(physicsComponent->GetPushBox());
}

void UPhysicsWorld::RegisteEnvironmentCollisionBox(UEnviormentCollisionBox * box)
{
	if (box == nullptr)
		return;

	if (!EnviormentCollisionBoxes.Contains(box))
		EnviormentCollisionBoxes.Add(box);

	if (!PhysicsBoxes.Contains(box))
		PhysicsBoxes.Add(box);
}

