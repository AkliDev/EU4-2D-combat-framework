// Fill out your copyright notice in the Description page of Project Settings.


#include "Physics/FGPhysicsComponent.h"
#include "Game/FightanProjectGameModeBase.h"

// Sets default values for this component's properties
UFGPhysicsComponent::UFGPhysicsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UFGPhysicsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (PushBox != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Sub"));
		PushBox->OnTransformChange.AddDynamic(this, &UFGPhysicsComponent::UpdateLocation);
		PushBox->SetRelativeLocation(Container->GetRelativeTransform().GetLocation() + FVector(0, 0, PushBox->GetScaledBoxExtent().Z));
	}

	if (AFightanProjectGameModeBase* gameMode = Cast<AFightanProjectGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		gameMode->GetPhysicsWorld()->RegistePhysicsComponent(this);
	}
}

void UFGPhysicsComponent::SetPushBoxZOffsetOnChange()
{
	if (PushBox == nullptr)
		return;

	if (PushBox->GetScaledBoxExtent().Z != PreviousPushBoxZExtend && PushBox != nullptr && Container != nullptr)
		PushBox->SetRelativeLocation(Container->GetRelativeTransform().GetLocation() + FVector(0, 0, PushBox->GetScaledBoxExtent().Z));

	PreviousPushBoxZExtend = PushBox->GetScaledBoxExtent().Z;
}

void UFGPhysicsComponent::UpdateLocation()
{
	if (PreviousPushBoxRelativePosition != PushBox->GetRelativeTransform().GetLocation())
		Container->SetWorldLocation(PushBox->GetComponentToWorld().GetLocation() - FVector(0, 0, PushBox->GetScaledBoxExtent().Z));

	PreviousPushBoxRelativePosition = PushBox->GetRelativeTransform().GetLocation();
}

void UFGPhysicsComponent::AddGravity(float DeltaTime)
{
	Velocity.Z -= 1500 * DeltaTime;
}

// Called every frame
void UFGPhysicsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	SetPushBoxZOffsetOnChange();
	AddGravity(DeltaTime);

	CheckVelocityFlip();
	PreviousVelocity = Velocity;
}

void UFGPhysicsComponent::CheckVelocityFlip()
{
	if (FMath::Sign(PreviousVelocity.X) != FMath::Sign(Velocity.X))
		OnVelpcityFlipX.Broadcast(Events::ON_VELOCITY_FLIP_X);

	if (FMath::Sign(PreviousVelocity.Z) != FMath::Sign(Velocity.Z))
		OnVelpcityFlipX.Broadcast(Events::ON_VELOCITY_FLIP_Z);
}

void UFGPhysicsComponent::FireCollisionEvents(FVector Overlap)
{
	if (Overlap == FVector::ZeroVector)
		return;

	//Up Collison
	if (Overlap.Z < 0)
	{
		Velocity.Z = 0;
		OnCollisionUp.Broadcast(Events::ON_COLLISION_UP);
	}

	//Down Collison
	if (Overlap.Z > 0)
	{
		GEngine->AddOnScreenDebugMessage(1, 1, FColor::Cyan, TEXT("Down"));
		Velocity.Z = 0;
		OnCollisionDown.Broadcast(Events::ON_COLLISION_DOWN);
	}

	//Left Collison
	if (Overlap.X > 0)
	{
		Velocity.X = 0;
		OnCollisionBehind.Broadcast(Events::ON_COLLISION_BEHIND);
	}

	//Right Collision
	if (Overlap.X < 0)
	{
		Velocity.X = 0;
		OnCollisionFront.Broadcast(Events::ON_COLLISION_FRONT);
	}	
}

void UFGPhysicsComponent::SetPushBox(UPushBoxComponent * pushBox)
{
	PushBox = pushBox;
	PreviousPushBoxRelativePosition = PushBox->GetRelativeTransform().GetLocation();
	SetPushBoxZOffsetOnChange();
}

void UFGPhysicsComponent::SetContainer(UCharacterContainer * container)
{
	Container = container;
}

void UFGPhysicsComponent::SetVelocity(FVector velocityVector)
{
	Velocity = velocityVector;
}
