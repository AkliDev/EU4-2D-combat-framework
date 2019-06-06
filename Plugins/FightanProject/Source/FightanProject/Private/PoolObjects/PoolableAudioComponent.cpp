// Fill out your copyright notice in the Description page of Project Settings.

#include "PoolObjects/PoolableAudioComponent.h"

void UPoolableAudioComponent::BeginPlay()
{
	Super::BeginPlay();
	OnAudioFinished.AddDynamic(this, &UPoolableAudioComponent::SetInactive);
}

void UPoolableAudioComponent::SetInactive()
{
	bInUse = false;
}

void UPoolableAudioComponent::Init(USoundWave* soundWave, FVector position)
{
	bInUse = true;
	SetSound(soundWave);
	SetWorldLocation(position);
	Play();
}