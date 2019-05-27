// Fill out your copyright notice in the Description page of Project Settings.

#include "Physics/Collision/Box/EnviormentCollisionBox.h"
#include "Game/FightanProjectGameModeBase.h"

UEnviormentCollisionBox::UEnviormentCollisionBox()
{
	Type = PhysicsType::STATIC;
}

// Called when the game starts
void UEnviormentCollisionBox::BeginPlay()
{
	Super::BeginPlay();
	 
	if (AFightanProjectGameModeBase* gameMode = Cast<AFightanProjectGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		gameMode->GetPhysicsWorld()->RegisteEnvironmentCollisionBox(this);
	}
}
