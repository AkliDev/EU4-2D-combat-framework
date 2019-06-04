// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Physics/PhysicsWorld.h"
#include "Managers/HitManager.h"
#include "UMG/Public/Blueprint/UserWidget.h"
#include "Managers/ManagerContainer.h"
#include "FightanProjectGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class FIGHTANPROJECT_API AFightanProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AFightanProjectGameModeBase();

protected:
	/** Called when the game starts. */
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
		UPhysicsWorld* PhysicsWorld;

	UPROPERTY(VisibleAnywhere)
		UHitManager* HitManager;

	UPROPERTY(VisibleAnywhere)
		AManagerContainer* ManagerContainer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	/** The widgets instances that we are using as our menu. */
	UPROPERTY()
		UUserWidget* CurrentWidget;

	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

public:

	UFUNCTION()
		void AttachSceneComponent(USceneComponent* Subject, USceneComponent* DuctTape);

	UFUNCTION(BlueprintCallable, Category = "Components|Physics")
		UPhysicsWorld* GetPhysicsWorld() const;

	UFUNCTION(BlueprintCallable, Category = "Components|Hit Management")
		UHitManager* GetHitManager() const;

	AManagerContainer* GetManagerContainer() const;
};

FORCEINLINE UPhysicsWorld* AFightanProjectGameModeBase::GetPhysicsWorld() const
{
	return PhysicsWorld;
}

FORCEINLINE UHitManager* AFightanProjectGameModeBase::GetHitManager() const
{
	return HitManager;
}

FORCEINLINE AManagerContainer* AFightanProjectGameModeBase::GetManagerContainer() const
{
	return ManagerContainer;
}