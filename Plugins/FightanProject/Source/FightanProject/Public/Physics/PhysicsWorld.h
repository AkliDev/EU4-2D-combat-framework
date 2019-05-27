// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/Containers/Map.h"
#include "Components/ActorComponent.h"
#include "Physics/Collision/Box/FGCollisionBoxBase.h"
#include "Physics/Collision/CollisionUtility.h"
#include "Physics/Collision/Box/EnviormentCollisionBox.h"
#include "Physics/FGPhysicsComponent.h"
#include "PhysicsWorld.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FIGHTANPROJECT_API UPhysicsWorld : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPhysicsWorld();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere)
		int MaxSolveRecursionCount;

	UPROPERTY(EditAnywhere)
		TArray<UEnviormentCollisionBox*> EnviormentCollisionBoxes;

	UPROPERTY(EditAnywhere)
		TArray<UPhysicsBoxComponent*> PhysicsBoxes;

	UPROPERTY(EditAnywhere)
		TArray<UFGPhysicsComponent*> PhysicsEntities;

	UPROPERTY(EditAnywhere)
		TArray<UCastBox*> CurrentStateOfBoxes;

	void TranslatePushBoxes(float deltaTime);

	bool CheckPushPhysicsForBoxes(UCastBox* castBox, FVector displacement, UFGPhysicsComponent* refComponent);
	void UpdateCurrentStateOfBoxes();

	TArray<UPhysicsBoxComponent*> GetOverlapBoxes(UCastBox* castBox);
	TArray<UPhysicsBoxComponent*> GetOverlapBoxes(UFGCollisionBoxBase* castBox);

	TArray<UPhysicsBoxComponent*> GetDynamicOverlapBoxes(UCastBox* castBox);
	TArray<UPhysicsBoxComponent*> GetDynamicOverlapBoxes(UFGCollisionBoxBase* castBox);

	TArray<UPhysicsBoxComponent*> GetStaticOverlapBoxes(UCastBox* castBox);
	TArray<UPhysicsBoxComponent*> GetStaticOverlapBoxes(UFGCollisionBoxBase* castBox);

	TArray<UCastBox*> GetOverlapCurrentStateOfBoxes(UCastBox* castBox);


public:
	//Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RegistePhysicsComponent(UFGPhysicsComponent* physicsComponent);
	void RegisteEnvironmentCollisionBox(UEnviormentCollisionBox* box);
};
