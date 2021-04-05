#include "LastRequestManager.h"

#include "Plugin/LastRequest/LastRequest.h"

#include "PublicManager.h"

LastRequest* LastRequestManager::sActiveLastRequest = nullptr;
Menu LastRequestManager::sLastRequestMainMenus[MAXPLAYERS];

constexpr const char* const CloseFightInfoStr = "1";
constexpr const char* const Shot4ShotInfoStr = "2";
constexpr const char* const GunTossInfoStr = "3";
constexpr const char* const ChickenFightInfoStr = "4";
constexpr const char* const NoscopeInfoStr = "5";
constexpr const char* const HotPotatoInfoStr = "6";
constexpr const char* const DodgeBallInfoStr = "7";
constexpr const char* const RebelInfoStr = "8";

int LastRequestManager::LRHandler(Menu* menu, MenuAction action, int param1, int param2)
{
	if (action == MenuAction_Select)
	{
		char info[4];
		menu->GetItem(param2, info, sizeof(info));
		LastRequest::Type type = LastRequest::Type::None;

		if (!strcmp(info, CloseFightInfoStr))
			type = LastRequest::Type::CloseFight;
		else if (!strcmp(info, Shot4ShotInfoStr))
			type = LastRequest::Type::Shot4Shot;
		else if (!strcmp(info, GunTossInfoStr))
			type = LastRequest::Type::GunToss;
		else if (!strcmp(info, ChickenFightInfoStr))
			type = LastRequest::Type::ChickenFight;
		else if (!strcmp(info, NoscopeInfoStr))
			type = LastRequest::Type::Noscope;
		else if (!strcmp(info, HotPotatoInfoStr))
			type = LastRequest::Type::HotPotato;
		else if (!strcmp(info, DodgeBallInfoStr))
			type = LastRequest::Type::DodgeBall;
		else if (!strcmp(info, RebelInfoStr))
			type = LastRequest::Type::Rebel;

		LRCallbackFunc callback = reinterpret_cast<LRCallbackFunc>(menu->GetParam());
		callback(param1, type);
	}

	return 0;
}

void LastRequestManager::Init()
{
	for (int i = 0; i < MAXPLAYERS; ++i)
	{
		Menu& menu = sLastRequestMainMenus[i];
		menu = Menu(LRHandler);
	}
}

void LastRequestManager::Shutdown()
{
	for (int i = 0; i < MAXPLAYERS; ++i)
		sLastRequestMainMenus[i].Delete();
}

void LastRequestManager::Unset(int loser, int winner)
{
	delete sActiveLastRequest;
	sActiveLastRequest = nullptr;
}

void LastRequestManager::RefreshLastRequestMainMenu(int client)
{
	Menu& menu = sLastRequestMainMenus[client - 1];
	menu.RemoveAllItems();
	menu.SetTitle("Last Request");
	menu.AddItem(CloseFightInfoStr, "CloseFight");
	menu.AddItem(Shot4ShotInfoStr, "Shot4Shot");
	menu.AddItem(GunTossInfoStr, "GunToss");
	menu.AddItem(DodgeBallInfoStr, "DodgeBall");
	menu.AddItem(NoscopeInfoStr, "NoscopeFight");
	menu.AddItem(HotPotatoInfoStr, "HotPotato");
	menu.AddItem(ChickenFightInfoStr, "ChickenFight");
	menu.AddItem(RebelInfoStr, "RebelFight");
}

void LastRequestManager::DisplayLastRequestMainMenu(int client, LRCallbackFunc callback)
{
	Menu& menu = sLastRequestMainMenus[client - 1];
	menu.SetParam(callback);
	menu.DisplayToClient(client, 20);
}

void LastRequestManager::OnPlayerDeath(int victim)
{
	bool tPlayerVictim = sActiveLastRequest->GetPlayerT() == victim;
	if (tPlayerVictim || sActiveLastRequest->GetPlayerCT() == victim)
	{
		int winner = tPlayerVictim ? sActiveLastRequest->GetPlayerCT() : sActiveLastRequest->GetPlayerT();
		sActiveLastRequest->OnEnd(victim, winner);
		LastRequestManager::Unset();
	}
}
