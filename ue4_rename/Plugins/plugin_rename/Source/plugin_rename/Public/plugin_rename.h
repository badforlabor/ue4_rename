// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ModuleManager.h"

class FToolBarBuilder;
class FMenuBuilder;

class Fplugin_renameModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command (by default it will bring up plugin window) */
	void PluginButtonClicked();
	
private:

	void AddToolbarExtension(FToolBarBuilder& Builder);
	void AddMenuExtension(FMenuBuilder& Builder);

	TSharedRef<class SDockTab> OnSpawnPluginTab(const class FSpawnTabArgs& SpawnTabArgs);

private:
	TSharedPtr<class FUICommandList> PluginCommands;

private:
	// 界面处理
	TSharedPtr<SEditableText> edtPrefix;
	TSharedPtr<SEditableText> edtPostfix;
	TSharedPtr<SEditableText> edtPrefix1, edtPrefix2;
	TSharedPtr<SEditableText> edtPostfix1, edtPostfix2;
	FReply OnClickChangePrefix();
	FReply OnClickChangePostfix();
	FReply OnClickReplacePrefix();
	FReply OnClickReplacePostfix();

	TArray<AActor*> GetSelectedActors();
};