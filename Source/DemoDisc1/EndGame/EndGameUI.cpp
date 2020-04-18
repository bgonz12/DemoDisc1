// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGameUI.h"

bool UEndGameUI::Initialize()
{
	if (!Super::Initialize()) return false;

	PlayCurtainFadeIn(0.0f);

	return true;
}
