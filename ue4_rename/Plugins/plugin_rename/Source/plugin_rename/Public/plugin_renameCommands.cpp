// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "plugin_renamePrivatePCH.h"
#include "plugin_renameCommands.h"

#define LOCTEXT_NAMESPACE "Fplugin_renameModule"

void Fplugin_renameCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "plugin_rename", "Bring up plugin_rename window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
