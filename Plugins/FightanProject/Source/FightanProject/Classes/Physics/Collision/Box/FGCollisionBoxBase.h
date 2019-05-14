#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "FGCollisionBoxBase.generated.h"

/**
 *
 */

UENUM()
enum class PhysicsType : int8
{
	STATIC,
	DYNAMIC,
	TRIGGER
};


UCLASS()
class FIGHTANPROJECT_API UFGCollisionBoxBase : public UBoxComponent
{
	GENERATED_BODY()

public:
	UFGCollisionBoxBase();

	FVector GetCenterOfBox();
	FVector GetMaxOfBox();
	FVector GetMinOfBox();
	float GetUpOfBox();
	float GetDownOfBox();
	float GetLeftOfBox();
	float GetRightOfBox();
	PhysicsType GetPhysicsType();
protected:
	UPROPERTY(EditAnywhere)
		PhysicsType Type;
};

FORCEINLINE FVector UFGCollisionBoxBase::GetCenterOfBox()
{
	return GetComponentToWorld().GetLocation();
}

FORCEINLINE FVector UFGCollisionBoxBase::GetMaxOfBox()
{
	return GetComponentToWorld().GetLocation() + GetScaledBoxExtent();
}

FORCEINLINE FVector UFGCollisionBoxBase::GetMinOfBox()
{
	return GetComponentToWorld().GetLocation() - GetScaledBoxExtent();
}

FORCEINLINE float UFGCollisionBoxBase::GetUpOfBox()
{
	return GetComponentToWorld().GetLocation().Z + GetScaledBoxExtent().Z;
}

FORCEINLINE float UFGCollisionBoxBase::GetDownOfBox()
{
	return GetComponentToWorld().GetLocation().Z - GetScaledBoxExtent().Z;
}

FORCEINLINE float UFGCollisionBoxBase::GetLeftOfBox()
{
	return GetComponentToWorld().GetLocation().X - GetScaledBoxExtent().X;
}

FORCEINLINE float UFGCollisionBoxBase::GetRightOfBox()
{
	return GetComponentToWorld().GetLocation().X + GetScaledBoxExtent().X;
}

FORCEINLINE PhysicsType UFGCollisionBoxBase::GetPhysicsType()
{
	return Type;
}

UCLASS()
class FIGHTANPROJECT_API UCastBox : public UObject
{
	GENERATED_BODY()

public:
	UCastBox();
	UCastBox(FVector position, FVector extends);
	UCastBox(UFGCollisionBoxBase* castBox);

	void Init(FVector position, FVector extent);
	void Init(UFGCollisionBoxBase* castBox);

private:
	UPROPERTY(EditAnywhere)
		UFGCollisionBoxBase* BoxRef;
	UPROPERTY(EditAnywhere)
		FVector Position;
	UPROPERTY(EditAnywhere)
		FVector Extent;
	UPROPERTY(EditAnywhere)
		PhysicsType Type;
public:

	void Update();

	UFGCollisionBoxBase* GetBoxRef();
	FVector GetPosition();
	FVector GetExtent();
	PhysicsType GetType();

	void SetPosition(FVector value);
	void SetType(PhysicsType value);

	void AddToPosition(FVector value);
};

FORCEINLINE UFGCollisionBoxBase*  UCastBox::GetBoxRef()
{
	return BoxRef;
}
FORCEINLINE FVector  UCastBox::GetPosition()
{
	return Position;
}
FORCEINLINE FVector UCastBox::GetExtent()
{
	return Extent;
}
FORCEINLINE PhysicsType UCastBox::GetType()
{
	return Type;
}

FORCEINLINE void UCastBox::SetPosition(FVector value)
{
	Position = value;
}

FORCEINLINE void UCastBox::SetType(PhysicsType value)
{
	Type = value;
}

FORCEINLINE void  UCastBox::AddToPosition(FVector value)
{
	Position += value;
}