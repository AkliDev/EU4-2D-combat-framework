// Fill out your copyright notice in the Description page of Project Settings.


#include "SFXManager.h"

// Sets default values for this component's properties
USFXManager::USFXManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	// ...
	AudioComponentPoolSize = 20;
	SetMobility(EComponentMobility::Static);
}

// Called when the game starts
void USFXManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
	for (int i = 0; i < AudioComponentPoolSize; i++)
	{
		AudioComponentPool.Add(CreateUAudioComponentComponent());
	}
}

UPoolableAudioComponent* USFXManager::CreateUAudioComponentComponent()
{
	UPoolableAudioComponent* pComponent = NewObject<UPoolableAudioComponent>(this);
	pComponent->RegisterComponent();
	pComponent->GetRelativeTransform().SetLocation(FVector::ZeroVector);
	return pComponent;
}

// Called every frame
void USFXManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UPoolableAudioComponent* USFXManager::ActivateAudioComponent(USoundWave* soundWave, FVector postion)
{
	//search in the pool for a AudioComponent that we can use. If one is found we call init on it and return it
	for (UPoolableAudioComponent* audio : AudioComponentPool)
	{
		if (audio->bInUse == false)
		{
			audio->Init(soundWave, postion);
			return audio;
		}
	}

	//if all AudioComponents are in use the increase the amount of AudioComponents in the pool
	for (int i = 0; i < AudioComponentPoolSize; i++)
	{
		AudioComponentPool.Add(CreateUAudioComponentComponent());
	}

	//After we increased the amount of AudioComponents we search for one again and return it. 
	return ActivateAudioComponent(soundWave, postion);
}