// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BufferItem.generated.h"

/**
 *
 */
UCLASS(BlueprintType)
class FIGHTANPROJECT_API UBufferItem : public UObject
{
	GENERATED_BODY()
public:
	UBufferItem();
	UBufferItem(float timeStamp);

	UPROPERTY(EditAnywhere)
		float BeginTimeStamp;
	UPROPERTY(EditAnywhere)
		float EndTimeStamp;

	//Returns delta between the begin time and end time
	float GetDurationTime();
	//Returns time difference betweein this buffer item and the given buffer item
	float GetTimeDifferenceWithOtherItem(UBufferItem* OtherBufferItem);
	//returns age of the item from when it was registered 
	float GetInputAgeFromBeginTime(float currentTime);
	//returns age of the item from when it was  
	float GetInputAgeFromEndTime(float currentTime);
};

