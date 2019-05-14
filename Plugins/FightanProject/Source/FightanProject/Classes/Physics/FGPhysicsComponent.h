// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Classes/Kismet/KismetMathLibrary.h"
#include "Collision/Box/PushBoxComponent.h"
#include "Character/CharacterContainer.h"
#include "StateMachine/Events/EventEnums.h"
#include "FGPhysicsComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCOllisionUp, Events, event);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCOllisionDown, Events, event);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCOllisionBehind, Events, event);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCOllisionFront, Events, event);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVelpcityFlipX, Events, event);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVelpcityFlipZ, Events, event);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FIGHTANPROJECT_API UFGPhysicsComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFGPhysicsComponent();

protected:

	UPROPERTY(VisibleAnywhere)
		UPushBoxComponent* PushBox;

	UPROPERTY(VisibleAnywhere)
		UCharacterContainer* Container;

	UPROPERTY(EditAnywhere)
		FVector Velocity;

	UPROPERTY(EditAnywhere)
		FVector PreviousVelocity;

	float PreviousPushBoxZExtend;
	FVector PreviousPushBoxRelativePosition;

	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
		void SetPushBoxZOffsetOnChange();
	UFUNCTION()
		void UpdateLocation();

	UFUNCTION()
		void AddGravity(float DeltaTime);

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void CheckVelocityFlip();
	void FireCollisionEvents(FVector OverLap);

	void SetPushBox(UPushBoxComponent* pushBox);
	void SetContainer(UCharacterContainer* container);

	UFUNCTION(BlueprintCallable)
		void SetVelocity(FVector velocityVector);

	//CollisionEvents
	FOnCOllisionUp OnCollisionUp;
	FOnCOllisionDown OnCollisionDown;
	FOnCOllisionBehind OnCollisionBehind;
	FOnCOllisionFront OnCollisionFront;


	//VelocityEvents
	FOnVelpcityFlipX OnVelpcityFlipX;
	FOnVelpcityFlipZ OnVelpcityFlipZ;
	

	UPushBoxComponent* GetPushBox() const;
	FVector GetVelocity() const;
};

FORCEINLINE UPushBoxComponent* UFGPhysicsComponent::GetPushBox() const
{
	return PushBox;
}

FORCEINLINE FVector UFGPhysicsComponent::GetVelocity() const
{
	return Velocity;
}