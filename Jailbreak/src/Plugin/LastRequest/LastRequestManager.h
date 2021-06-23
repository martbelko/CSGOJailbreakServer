#pragma once

#include "Menu.h"

#include "Plugin/LastRequest/LastRequest.h"

class LastRequestManager
{
	using LRCallbackFunc = void (*)(int client, LastRequest::Type type);
public:
	LastRequestManager() = delete;

	static void Init();

	template<typename T, typename ... Args>
	static void Set(Args&& ... args)
	{
		sActiveLastRequest = new T(args...);
	}

	static void Unset(int loser = -1, int winner = -1);

	static void TranslateLastRequestMainMenu(int client);
	static void DisplayLastRequestMainMenu(int client, LRCallbackFunc callback);

	static LastRequest* GetActiveLastRequest() { return sActiveLastRequest; }

	static void OnPlayerDeath(int victim);
private:
	static int LRHandler(Menu* menu, MenuAction action, int param1, int param2);
private:
	static LastRequest* sActiveLastRequest;
	static Menu sLastRequestMainMenus[MAXPLAYERS];
private:
	static constexpr const char* const sCloseFightInfoStr = "1";
	static constexpr const char* const sShot4ShotInfoStr = "2";
	static constexpr const char* const sGunTossInfoStr = "3";
	static constexpr const char* const sChickenFightInfoStr = "4";
	static constexpr const char* const sNoscopeInfoStr = "5";
	static constexpr const char* const sHotPotatoInfoStr = "6";
	static constexpr const char* const sDodgeBallInfoStr = "7";
	static constexpr const char* const sRebelInfoStr = "8";
};