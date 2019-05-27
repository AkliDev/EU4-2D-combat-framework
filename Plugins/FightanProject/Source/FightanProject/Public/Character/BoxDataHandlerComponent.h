// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Physics/Collision/Box/TraceBox.h"
#include "Physics/Collision/Box/HitBox.h"
#include "Physics/Collision/Box/HurtBox.h"
#include "BoxDataHandlerComponent.generated.h"

class AFightPawn;
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FIGHTANPROJECT_API UBoxDataHandlerComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBoxDataHandlerComponent();

protected:
	friend class AFightPawn;

	AFightPawn* OwningPawns;

	UPROPERTY(EditAnywhere)
		int HitBoxPoolSize;
		int HurtBoxPoolSize;

	UPROPERTY(EditAnywhere)
		TArray<UTraceBox*> BoxPool;

	UPROPERTY(EditAnywhere)
		TArray<UTraceBox*> ActiveBoxes;

	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
		UTraceBox* CreateTraceBox();

	UFUNCTION()
		UHitBox* CreateHitBox();

	UFUNCTION()
		UHurtBox* CreateHurtBox();

	UHitBox* ActivateHitBox(FBoxParams& params);
	UHurtBox* ActivateHurtBox(FBoxParams& params);

	void DeactivateAllActiveBoxes();

public:

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetOwningPawn(AFightPawn* owningPawn);
};