// Fill out your copyright notice in the Description page of Project Settings.

#include "Game/FightanProjectGameModeBase.h"

AFightanProjectGameModeBase::AFightanProjectGameModeBase()
{
	PhysicsWorld = CreateDefaultSubobject<UPhysicsWorld>(TEXT("PhysicsWorld"));
	HitManager = CreateDefaultSubobject<UHitManager>(TEXT("HitManager"));
}

void AFightanProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	ManagerContainer = GetWorld()->SpawnActor<AManagerContainer>(FVector::ZeroVector, FRotator::ZeroRotator);
	ChangeMenuWidget(StartingWidgetClass);
}

void AFightanProjectGameModeBase::ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass)
{
	if (CurrentWidget != nullptr)
	{
		CurrentWidget->RemoveFromViewport();
		CurrentWidget = nullptr;
	}

	if (NewWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), NewWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}
}

void AFightanProjectGameModeBase::AttachSceneComponent(USceneComponent* Subject, USceneComponent* DuctTape)
{
	Subject->AttachToComponent(DuctTape, FAttachmentTransformRules::KeepRelativeTransform);
}