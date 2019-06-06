// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PoolObjects/PoolableAudioComponent.h"
#include "SFXManager.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FIGHTANPROJECT_API USFXManager : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USFXManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		int AudioComponentPoolSize;

	UPROPERTY(EditAnywhere)
		TArray<UPoolableAudioComponent*> AudioComponentPool;

	UPoolableAudioComponent* CreateUAudioComponentComponent();

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPoolableAudioComponent* ActivateAudioComponent(USoundWave* soundWave, FVector postion);
};
