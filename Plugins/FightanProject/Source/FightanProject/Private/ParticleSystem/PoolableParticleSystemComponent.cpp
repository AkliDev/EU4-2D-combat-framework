// Fill out your copyright notice in the Description page of Project Settings.

#include "ParticleSystem/PoolableParticleSystemComponent.h"

void UPoolableParticleSystemComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPoolableParticleSystemComponent::Init(UParticleSystem* particleTemplate, FVector position, FRotator rotation, FVector scale)
{
	bInUse = true;
	SetTemplate(particleTemplate);
	SetWorldLocation(position);
	Activate();
}