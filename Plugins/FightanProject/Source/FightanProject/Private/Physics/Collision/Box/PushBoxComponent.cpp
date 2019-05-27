// Fill out your copyright notice in the Description page of Project Settings.


#include "Physics/Collision/Box/PushBoxComponent.h"

UPushBoxComponent::UPushBoxComponent()
{
	Type = PhysicsType::DYNAMIC;
	bWantsOnUpdateTransform = true;

	ShapeColor = FColor::Green;
}

//void UPushBoxComponent::SetBoxExtent(FVector InBoxExtent, bool bUpdateOverlaps)
//{
//	UE_LOG(LogTemp, Warning, TEXT("Your message"));
//	SetWorldLocation(GetComponentLocation() + FVector(0, 0, InBoxExtent.Z - BoxExtent.Z));
//	UBoxComponent::SetBoxExtent(InBoxExtent, bUpdateOverlaps);
//}
void UPushBoxComponent::OnUpdateTransform(EUpdateTransformFlags UpdateTransformFlags, ETeleportType Teleport)
{
	Super::OnUpdateTransform(UpdateTransformFlags, Teleport);
	OnTransformChange.Broadcast();
}
