// Fill out your copyright notice in the Description page of Project Settings.

#include "HitManager.h"
#include "Character/BoxDataHandlerComponent.h"
#include "Physics/Collision/CollisionUtility.h"
#include "Physics/Collision/Box/TraceBox.h"
#include "Physics/Collision/Box/HitBox.h"
#include "Physics/Collision/Box/HurtBox.h"

// Sets default values for this component's properties
UHitManager::UHitManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UHitManager::BeginPlay()
{
	Super::BeginPlay();

	// ...
}

void UHitManager::CheckForOverlaps()
{
	for (AFightPawn* pawn : ActivePawns)
	{
		for (AFightPawn* pawnOther : ActivePawns)
		{
			if (pawn != pawnOther)
			{
				for (UHitBox* hitBox : pawn->GetBoxDataHandlerComponent()->ActiveHitBoxes)
				{
					for (UHurtBox* hurtBox : pawnOther->GetBoxDataHandlerComponent()->ActiveHurtBoxes)
					{
						if (UCollisionUtility::AreBoxesIntersecting(hitBox, hurtBox) && !hitBox->HitPawns.Contains(pawnOther))
						{
							hitBox->HitPawns.Add(pawnOther);
							pawnOther->BroadCastOnIsHit();
							pawn->BroadCastOnHasHit();					
						}
					}
				}
			}
		}
	}
}

// Called every frame
void UHitManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	CheckForOverlaps();
}

void UHitManager::RegisterPawn(AFightPawn* pawnToRegister)
{
	if(!ActivePawns.Contains(pawnToRegister))
	ActivePawns.Add(pawnToRegister);
}