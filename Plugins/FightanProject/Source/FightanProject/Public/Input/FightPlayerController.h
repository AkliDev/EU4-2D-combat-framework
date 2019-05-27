// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputEnums.h"
#include "GameFramework/PlayerController.h"
#include "FightPlayerController.generated.h"

//Event when new input is given by the player
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewInput, uint32, controllerBitFlag);

UCLASS()
class FIGHTANPROJECT_API AFightPlayerController : public APlayerController
{
	GENERATED_BODY()
	

protected:
	virtual void SetupInputComponent() override;
	
	void UpPressed();
	void UpReleased();

	void DownPressed();
	void DownReleased();

	void LeftPressed();
	void LeftReleased();

	void RightPressed();
	void RightReleased();

	void Button1Pressed();
	void Button1Released();

	void Button2Pressed();
	void Button2Released();

	void Button3Pressed();
	void Button3Released();

	void Button4Pressed();
	void Button4Released();

	void Button5Pressed();
	void Button5Released();

	void Button6Pressed();
	void Button6Released();

	UPROPERTY(EditAnywhere)
		uint32 ControllerBitFlag;

public:
	FOnNewInput NewInput;

	//Player input stored in one bitflag
	uint32 GetControllerBitFlag();
};
