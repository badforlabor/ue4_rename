// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "plugin_renamePrivatePCH.h"

#include "SlateBasics.h"
#include "SlateExtras.h"

#include "plugin_renameStyle.h"
#include "plugin_renameCommands.h"

#include "LevelEditor.h"

static const FName plugin_renameTabName("plugin_rename");

#define LOCTEXT_NAMESPACE "Fplugin_renameModule"

void Fplugin_renameModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	Fplugin_renameStyle::Initialize();
	Fplugin_renameStyle::ReloadTextures();

	Fplugin_renameCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		Fplugin_renameCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &Fplugin_renameModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &Fplugin_renameModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &Fplugin_renameModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(plugin_renameTabName, FOnSpawnTab::CreateRaw(this, &Fplugin_renameModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("Fplugin_renameTabTitle", "plugin_rename"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void Fplugin_renameModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	Fplugin_renameStyle::Shutdown();

	Fplugin_renameCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(plugin_renameTabName);
}

TSharedRef<SDockTab> Fplugin_renameModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("Fplugin_renameModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("plugin_rename.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
#if false
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
#else
			SNew(SVerticalBox)
			+SVerticalBox::Slot().MaxHeight(30)
			[
				SNew(SHorizontalBox)				
				+ SHorizontalBox::Slot()
				[
					SAssignNew(edtPrefix, SEditableText)
					.Text(FText::FromString(TEXT("prefix")))
				]
				+ SHorizontalBox::Slot().HAlign(HAlign_Left)
				[
					SNew(SButton)
					.Text(FText::FromString(TEXT("Ìí¼ÓÇ°×º")))
					.OnClicked_Raw(this, &Fplugin_renameModule::OnClickChangePrefix)
				]
			]
			+ SVerticalBox::Slot().MaxHeight(30)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SAssignNew(edtPostfix, SEditableText)
					.Text(FText::FromString(TEXT("postfix")))
				]
				+ SHorizontalBox::Slot().HAlign(HAlign_Left)
				[
					SNew(SButton)
					.Text(FText::FromString(TEXT("Ìí¼Óºó×º")))
					.OnClicked_Raw(this, &Fplugin_renameModule::OnClickChangePostfix)
				]
			]
			+ SVerticalBox::Slot().MaxHeight(30)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SAssignNew(edtPrefix1, SEditableText)
					.Text(FText::FromString(TEXT("old_prefix")))
				]
				+ SHorizontalBox::Slot()
				[
					SAssignNew(edtPrefix2, SEditableText)
					.Text(FText::FromString(TEXT("new_prefix")))
				]
				+ SHorizontalBox::Slot().HAlign(HAlign_Left)
				[
					SNew(SButton)
					.Text(FText::FromString(TEXT("Ìæ»»Ç°×º")))
					.OnClicked_Raw(this, &Fplugin_renameModule::OnClickReplacePrefix)
				]
			]
			+ SVerticalBox::Slot().MaxHeight(30)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				[
					SAssignNew(edtPostfix1, SEditableText)
					.Text(FText::FromString(TEXT("old_postfix")))
				]
				+ SHorizontalBox::Slot()
				[
					SAssignNew(edtPostfix2, SEditableText)
					.Text(FText::FromString(TEXT("new_postfix")))
				]
				+ SHorizontalBox::Slot().HAlign(HAlign_Left)
				[
					SNew(SButton)
					.Text(FText::FromString(TEXT("Ìæ»»ºó×º")))
					.OnClicked_Raw(this, &Fplugin_renameModule::OnClickReplacePostfix)
				]
			]
#endif
		];
}
FReply Fplugin_renameModule::OnClickChangePrefix()
{
	TArray<AActor*> actors = GetSelectedActors();
	for (int i = 0; i < actors.Num(); i++)
	{
		AActor* actor = actors[i];
		if (actor != NULL)
		{
			FString tmpName = actor->GetActorLabel();
			if (!tmpName.StartsWith(edtPrefix->GetText().ToString()))
			{
				actor->SetActorLabel(FString::Printf(TEXT("%s_%s"), *(edtPrefix->GetText().ToString()), *tmpName));
			}
		}
	}
	return FReply::Handled();
}
FReply Fplugin_renameModule::OnClickChangePostfix()
{
	TArray<AActor*> actors = GetSelectedActors();
	for (int i = 0; i < actors.Num(); i++)
	{
		AActor* actor = actors[i];
		if (actor != NULL)
		{
			FString tmpName = actor->GetActorLabel();
			if (!tmpName.EndsWith(edtPostfix->GetText().ToString()))
			{
				actor->SetActorLabel(FString::Printf(TEXT("%s_%s"), *tmpName, *(edtPostfix->GetText().ToString())));
			}
		}
	}
	return FReply::Handled();
}
FReply Fplugin_renameModule::OnClickReplacePrefix()
{
	TArray<AActor*> actors = GetSelectedActors();
	for (int i = 0; i < actors.Num(); i++)
	{
		AActor* actor = actors[i];
		if (actor != NULL)
		{
			FString tmpName = actor->GetActorLabel();
			
			if (tmpName.StartsWith(edtPrefix1->GetText().ToString()))
			{
				actor->SetActorLabel(FString::Printf(TEXT("%s_%s"), 
					*(edtPrefix2->GetText().ToString()), 
					*tmpName.Mid(edtPrefix1->GetText().ToString().Len())));
			}
		}
	}
	return FReply::Handled();
}
FReply Fplugin_renameModule::OnClickReplacePostfix()
{
	TArray<AActor*> actors = GetSelectedActors();
	for (int i = 0; i < actors.Num(); i++)
	{
		AActor* actor = actors[i];
		if (actor != NULL)
		{
			FString tmpName = actor->GetActorLabel();

			if (tmpName.EndsWith(edtPostfix1->GetText().ToString()))
			{
				actor->SetActorLabel(FString::Printf(TEXT("%s_%s"), 
					*tmpName.Mid(0, tmpName.Len() - edtPostfix1->GetText().ToString().Len()),
					*(edtPostfix2->GetText().ToString())));
			}
		}
	}
	return FReply::Handled();
}
TArray<AActor*> Fplugin_renameModule::GetSelectedActors()
{
	int SelectedCnt = 0;
	TArray<AActor*> ret;
	if (GEditor->GetSelectedActors() != NULL && GEditor->GetSelectedActors()->Num() > 0)
	{
		SelectedCnt = GEditor->GetSelectedActors()->Num();
		for (int i = 0; i < SelectedCnt; i++)
		{
			AActor* actor = CastChecked<AActor>(GEditor->GetSelectedActors()->GetSelectedObject(i));
			if (actor != NULL)
			{
				ret.Add(actor);
			}
		}
	}
	return ret;
}


void Fplugin_renameModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(plugin_renameTabName);
}

void Fplugin_renameModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(Fplugin_renameCommands::Get().OpenPluginWindow);
}

void Fplugin_renameModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(Fplugin_renameCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(Fplugin_renameModule, plugin_rename)