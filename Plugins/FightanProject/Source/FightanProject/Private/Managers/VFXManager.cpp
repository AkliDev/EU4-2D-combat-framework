// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/VFXManager.h"
#include "Game/FightanProjectGameModeBase.h"

// Sets default values for this component's properties
UVFXManager::UVFXManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	ParticlePoolSize = 25;
}


// Called when the game starts
void UVFXManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	for (int i = 0; i < ParticlePoolSize; i++)
	{
		ParticleSystemPool.Add(CreateParticleSystemComponent());
	}
}

UPoolableParticleSystemComponent*  UVFXManager::CreateParticleSystemComponent()
{
	UPoolableParticleSystemComponent* pComponent = NewObject<UPoolableParticleSystemComponent>(this);
	pComponent->RegisterComponent();
	pComponent->GetRelativeTransform().SetLocation(FVector::ZeroVector);
	return pComponent;
}

UPoolableParticleSystemComponent* UVFXManager::ActivateParticleSystemComponent(UParticleSystem* particleTemplate, FVector position, FRotator rotation, FVector scale)
{
	//search in the pool for a hitbox that we can use. If one is found we call init on it and return it
	for (UPoolableParticleSystemComponent* particle : ParticleSystemPool)
	{
		if (particle->bInUse == false)
		{
			particle->Init(particleTemplate, position, rotation, scale);
			return particle;
		}
	}
	//if all boxes are in use the increase the amount of hit boxes in the pool
	for (int i = 0; i < ParticlePoolSize; i++)
	{
		ParticleSystemPool.Add(CreateParticleSystemComponent());
	}

	//After we increased the amount of boxes we search for one again and return it. 
	return ActivateParticleSystemComponent(particleTemplate, position, rotation, scale);

}


// Called every frame
void UVFXManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}