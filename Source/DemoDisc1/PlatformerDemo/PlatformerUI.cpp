// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerUI.h"

bool UPlatformerUI::Initialize()
{
	if(!Super::Initialize()) return false;

	PlayCurtainFadeIn();

	PlayShowCollectables();

	return true;
}