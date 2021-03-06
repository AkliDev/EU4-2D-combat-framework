// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VFXManager.h"
#include "SFXManager.h"
#include "ManagerContainer.generated.h"

UCLASS()
class FIGHTANPROJECT_API AManagerContainer : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AManagerContainer();

protected:

	UPROPERTY(VisibleAnywhere)
		UVFXManager* VFXManager;
	UPROPERTY(VisibleAnywhere)
		USFXManager* SFXManager;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UVFXManager* GetVFXManager() const;
	USFXManager* GetSFXManager() const;

};

FORCEINLINE UVFXManager* AManagerContainer::GetVFXManager() const
{
	return VFXManager;
}
FORCEINLINE USFXManager* AManagerContainer::GetSFXManager() const
{
	return SFXManager;
}