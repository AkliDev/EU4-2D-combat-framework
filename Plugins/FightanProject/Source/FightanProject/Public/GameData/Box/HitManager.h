// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/FightPawn.h"
#include "HitManager.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FIGHTANPROJECT_API UHitManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHitManager();

protected:

	UPROPERTY(EditAnywhere)
		TArray<AFightPawn*> ActivePawns;
	// Called when the game starts
	virtual void BeginPlay() override;

	void CheckForOverlaps();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RegisterPawn(AFightPawn* pawnToRegister);
};
