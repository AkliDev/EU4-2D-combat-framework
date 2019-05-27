// Fill out your copyright notice in the Description page of Project Settings.


#include "Physics/Collision/Box/FGCollisionBoxBase.h"


UFGCollisionBoxBase::UFGCollisionBoxBase()
{
	BoxExtent.Y = 0;
	LineThickness = 5;
	bHiddenInGame = false;
}

UCastBox::UCastBox() {}
UCastBox::UCastBox(FVector position, FVector extent)
	:BoxRef(nullptr), Position(position), Extent(extent), Type(PhysicsType::STATIC) {}

UCastBox::UCastBox(UFGCollisionBoxBase* boxRef)
	: UCastBox()
{
	if (boxRef != nullptr)
	{
		BoxRef = boxRef;
		Position = boxRef->GetCenterOfBox();
		Extent = boxRef->GetScaledBoxExtent();
		Type = boxRef->GetPhysicsType();
	}
}

void UCastBox::Init(FVector position, FVector extent)
{
	BoxRef = nullptr;
	Position = position;
	Extent = extent;
	Type = PhysicsType::STATIC;
}

void UCastBox::Init(UFGCollisionBoxBase* refBox)
{
	if (refBox != nullptr)
	{
		BoxRef = refBox;
		Position = refBox->GetCenterOfBox();
		Extent = refBox->GetScaledBoxExtent();
		Type = refBox->GetPhysicsType();
	}
}

void UCastBox::Update()
{
	if (BoxRef != nullptr)
	{
		Position = BoxRef->GetCenterOfBox();
		Extent = BoxRef->GetScaledBoxExtent();
		Type = BoxRef->GetPhysicsType();
	}
}
