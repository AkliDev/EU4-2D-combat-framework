// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/InputBuffer/BufferItem.h"

UBufferItem::UBufferItem()
{
	BeginTimeStamp = 0.0f;
	EndTimeStamp = 0.0f;
}

UBufferItem::UBufferItem(float timeStamp)
	: BeginTimeStamp(timeStamp)
{

}

float UBufferItem::GetDurationTime()
{
	return EndTimeStamp - BeginTimeStamp;
}

float UBufferItem::GetTimeDifferenceWithOtherItem(UBufferItem* OtherBufferItem)
{
	return FMath::Abs(OtherBufferItem->BeginTimeStamp - EndTimeStamp);
}

float UBufferItem::GetInputAgeFromBeginTime(float currentTime)
{
	float inputAge = currentTime - BeginTimeStamp;
	return inputAge;
}

float UBufferItem::GetInputAgeFromEndTime(float currentTime)
{
	float inputAge = currentTime - EndTimeStamp;
	return inputAge;
}
