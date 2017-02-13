// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SlateBasics.h"
#include "plugin_renameStyle.h"

class Fplugin_renameCommands : public TCommands<Fplugin_renameCommands>
{
public:

	Fplugin_renameCommands()
		: TCommands<Fplugin_renameCommands>(TEXT("plugin_rename"), NSLOCTEXT("Contexts", "plugin_rename", "plugin_rename Plugin"), NAME_None, Fplugin_renameStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};