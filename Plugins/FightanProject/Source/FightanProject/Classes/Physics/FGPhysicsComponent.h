// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Classes/Kismet/KismetMathLibrary.h"
#include "Collision/Box/PushBoxComponent.h"
#include "Character/CharacterContainer.h"
#include "StateMachine/Events/EventEnums.h"
#include "FGPhysicsComponent.generated.h"

class AFightPawn;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhysicsEvent, Events, event);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FIGHTANPROJECT_API UFGPhysicsComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFGPhysicsComponent();

protected:

	AFightPawn* OwningPawn;

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

	

	void CheckVelocityFlip();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		void AddGravity(float DeltaTime);

	void FireCollisionEvents(FVector OverLap);

	void SetOwningPawn(AFightPawn* owningPawn);
	void SetPushBox(UPushBoxComponent* pushBox);
	void SetContainer(UCharacterContainer* container);

	UFUNCTION(BlueprintCallable)
		void SetVelocity(FVector velocityVector);

	UFUNCTION(BlueprintCallable)
		void AddVelocity(FVector velocityVector);

	FOnPhysicsEvent OnPhysicsEvent;

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