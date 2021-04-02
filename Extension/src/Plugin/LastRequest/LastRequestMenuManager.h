#pragma once

#include "Menu.h"

#include <array>

class LastRequest;

class LastRequestMenuManager
{
public:
	static void Init(std::vector<LastRequest*>& lastRequests);
	static void Shutdown();

	static void RefreshItemsForClient(int client, const char* title);
	static void DisplayMenuForClient(int client);
private:
	static Menu sMainMenus[MAXPLAYERS];

	static std::vector<LastRequest*> sLastRequests;
};
