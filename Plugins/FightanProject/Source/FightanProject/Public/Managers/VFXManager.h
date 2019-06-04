// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ParticleSystem/PoolableParticleSystemComponent.h"
#include "VFXManager.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FIGHTANPROJECT_API UVFXManager : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UVFXManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		int ParticlePoolSize;

	UPROPERTY(EditAnywhere)
		TArray<UPoolableParticleSystemComponent*> ParticleSystemPool;

	UPoolableParticleSystemComponent* CreateParticleSystemComponent();
	
public:

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPoolableParticleSystemComponent* ActivateParticleSystemComponent(UParticleSystem* particle, FVector position, FRotator rotation, FVector scale);
};
