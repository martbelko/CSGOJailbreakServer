#include "AdminMenu.h"

AdminMenu::AdminMenu()
{
	InitializeMenusArray(mMainMenus, MainMenuHandler);
	InitializeMenusArray(mPlayerCommandMenus, PlayerCommandsMenuHandler);
	InitializeMenusArray(mServerCommandMenus, ServerCommandsMenuHandler);
	InitializeMenusArray(mVotingCommandMenus, VotingCommandsMenuHandler);
}

void AdminMenu::ShowMenu(int client)
{
	mMainMenus[client - 1].DisplayToClient(client, 20);
}

void AdminMenu::Translate(int client)
{
	// TODO: Translate
	Menu& menu = mMainMenus[client - 1];
	menu.SetTitle("Admin Menu");
	menu.AddItem("Player Commands");
	menu.AddItem("Server Commands");
	menu.AddItem("Voting Commands");

	TranslateSubMenus(client);
}

void AdminMenu::TranslateSubMenus(int client)
{
	// TODO: Translate
	{
		Menu& menu = mPlayerCommandMenus[client - 1];
		menu.SetTitle("Player Commands");
		menu.AddItem("Ban");
		menu.AddItem("Kick");
		menu.AddItem("Mute");
		menu.AddItem("Burn");
	}

	{
		Menu& menu = mServerCommandMenus[client - 1];
		menu.SetTitle("Server Commands");
		menu.AddItem("Map Change");
		menu.AddItem("Make longer");
		menu.AddItem("Restart round");
		menu.AddItem("Restart game");
	}

	{
		Menu& menu = mVotingCommandMenus[client - 1];
		menu.SetTitle("Voting Commands");
		menu.AddItem("ban", "Ban");
		menu.AddItem("kick", "Kick");
		menu.AddItem("mute", "Mute");
		menu.AddItem("burn", "Burn");
	}
}

void AdminMenu::InitializeMenusArray(std::array<Menu, MAXPLAYERS>& menus, Menu::NewMenuHandler callback)
{
	for (Menu& menu : menus)
	{
		menu = Menu(callback);
		menu.SetParam(this);
	}
}

int AdminMenu::MainMenuHandler(Menu* menu, MenuAction action, int param1, int param2)
{
	if (action == MenuAction_Select)
	{
		int client = param1;
		char infoBuf[16];
		menu->GetItem(param2, infoBuf, sizeof(infoBuf));
		std::string_view infoStr(infoBuf);

		AdminMenu* adminMenu = reinterpret_cast<AdminMenu*>(menu->GetParam());
		if (infoStr == "0")
		{
			adminMenu->mPlayerCommandMenus[client - 1].DisplayToClient(client);
		}
		else if (infoStr == "1")
		{
			adminMenu->mServerCommandMenus[client - 1].DisplayToClient(client);
		}
		else
		{
			adminMenu->mVotingCommandMenus[client - 1].DisplayToClient(client);
		}
	}

	return 0;
}

int AdminMenu::PlayerCommandsMenuHandler(Menu* menu, MenuAction action, int param1, int param2)
{
	return 0;
}

int AdminMenu::ServerCommandsMenuHandler(Menu* menu, MenuAction action, int param1, int param2)
{
	return 0;
}

int AdminMenu::VotingCommandsMenuHandler(Menu* menu, MenuAction action, int param1, int param2)
{
	return 0;
}
