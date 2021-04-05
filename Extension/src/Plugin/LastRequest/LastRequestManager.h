#pragma once

#include "Menu.h"

#include "Plugin/LastRequest/LastRequest.h"

class LastRequestManager
{
	using LRCallbackFunc = void (*)(int client, LastRequest::Type type);
public:
	static void Init();
	static void Shutdown();

	template<typename T, typename ... Args>
	static void Set(Args&& ... args)
	{
		sActiveLastRequest = new T(args...);
	}

	static void Unset(int loser = -1, int winner = -1);

	static void RefreshLastRequestMainMenu(int client);
	static void DisplayLastRequestMainMenu(int client, LRCallbackFunc callback);

	static LastRequest* GetActiveLastRequest() { return sActiveLastRequest; }

	static void OnPlayerDeath(int victim);
private:
	static int LRHandler(Menu* menu, MenuAction action, int param1, int param2);
private:
	static LastRequest* sActiveLastRequest;
	static Menu sLastRequestMainMenus[MAXPLAYERS];
};