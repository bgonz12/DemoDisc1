// Fill out your copyright notice in the Description page of Project Settings.


#include "DemoDisc1GameInstance.h"

UDemoDisc1GameInstance::UDemoDisc1GameInstance()
{
	SpookLevel = 0;
	bHasSpookyTransitioned = false;
}

void UDemoDisc1GameInstance::TriggerSpookyTransition()
{
	OnSpookyTransition.Broadcast();
}

bool UDemoDisc1GameInstance::GetHasSpookyTransitioned()
{
	return bHasSpookyTransitioned;
}
