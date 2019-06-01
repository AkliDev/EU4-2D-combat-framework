// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Physics/Collision/Box/HitBox.h"
#include "Physics/Collision/Box/HurtBox.h"
#include "BoxDataHandlerComponent.generated.h"

class UHitManager;
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
	friend class UHitManager;

	AFightPawn* OwningPawns;

	UPROPERTY(EditAnywhere)
		int HitBoxPoolSize;
		int HurtBoxPoolSize;

	UPROPERTY(EditAnywhere)
		TArray<UTraceBox*> BoxPool;

	UPROPERTY(EditAnywhere)
		TArray<UHitBox*> ActiveHitBoxes;

	UPROPERTY(EditAnywhere)
		TArray<UHurtBox*> ActiveHurtBoxes;

	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
		UTraceBox* CreateTraceBox();

	UFUNCTION()
		UHitBox* CreateHitBox();

	UFUNCTION()
		UHurtBox* CreateHurtBox();

	UHitBox* ActivateHitBox(FBoxParams& params, FHitBoxParams& hitParams);
	UHurtBox* ActivateHurtBox(FBoxParams& params);

	void DeactivateAllActiveBoxes();

	// Called every frame by Owning pawn
	void UpdateComponent(float DeltaTime);

public:

	

	void SetOwningPawn(AFightPawn* owningPawn);
};