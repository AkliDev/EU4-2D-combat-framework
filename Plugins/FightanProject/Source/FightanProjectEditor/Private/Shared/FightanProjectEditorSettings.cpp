// Fill out your copyright notice in the Description page of Project Settings.


#include "FightanProjectEditorSettings.h"

#include "Misc/Paths.h"

UFightanProjectEditorSettings::UFightanProjectEditorSettings()
	: BackgroundColor(FLinearColor::Gray)
	, ForegroundColor(FLinearColor::Blue)
	, Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/DroidSansMono.ttf"), 10))
	, Margin(4.0f)
{}