// Fill out your copyright notice in the Description page of Project Settings.

#include "PoolObjects/PoolableParticleSystemComponent.h"

void UPoolableParticleSystemComponent::BeginPlay()
{
	Super::BeginPlay();
	OnSystemFinished.AddDynamic(this, &UPoolableParticleSystemComponent::SetInactive);
}

void UPoolableParticleSystemComponent::SetInactive(UParticleSystemComponent* pSystem)
{
	bInUse = false;
}

void UPoolableParticleSystemComponent::Init(UParticleSystem* particleTemplate, FVector position, FRotator rotation, FVector scale)
{
	bInUse = true;
	SetTemplate(particleTemplate);
	SetWorldLocation(position);
	Activate();
}