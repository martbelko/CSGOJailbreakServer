#pragma once

#include <CSGOExtension.h>

#include <array>

class AdminMenu final
{
public:
	AdminMenu();

	void ShowMenu(int client);
	void Translate(int client);
private:
	void TranslateSubMenus(int client);

	void InitializeMenusArray(std::array<Menu, MAXPLAYERS>& menus, Menu::NewMenuHandler callback);
private:
	static int MainMenuHandler(Menu* menu, MenuAction action, int param1, int param2);
	static int PlayerCommandsMenuHandler(Menu* menu, MenuAction action, int param1, int param2);
	static int ServerCommandsMenuHandler(Menu* menu, MenuAction action, int param1, int param2);
	static int VotingCommandsMenuHandler(Menu* menu, MenuAction action, int param1, int param2);
private:
	std::array<Menu, MAXPLAYERS> mMainMenus;
	std::array<Menu, MAXPLAYERS> mPlayerCommandMenus;
	std::array<Menu, MAXPLAYERS> mServerCommandMenus;
	std::array<Menu, MAXPLAYERS> mVotingCommandMenus;
};
