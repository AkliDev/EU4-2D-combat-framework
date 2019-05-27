// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Physics/PhysicsWorld.h"
#include "UMG/Public/Blueprint/UserWidget.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget> StartingWidgetClass;

	/** The widgets instances that we are using as our menu. */
	UPROPERTY()
		UUserWidget* CurrentWidget;

	void ChangeMenuWidget(TSubclassOf<UUserWidget> NewWidgetClass);

public:
	UFUNCTION(BlueprintCallable, Category = "Components|Physics")
	UPhysicsWorld* GetPhysicsWorld() const;
};

FORCEINLINE UPhysicsWorld* AFightanProjectGameModeBase::GetPhysicsWorld() const
{
	return PhysicsWorld;
}