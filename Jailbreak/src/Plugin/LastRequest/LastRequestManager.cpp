#include "LastRequestManager.h"

#include "Plugin/LastRequest/LastRequest.h"

#include "PublicManager.h"

LastRequest* LastRequestManager::sActiveLastRequest = nullptr;
Menu LastRequestManager::sLastRequestMainMenus[MAXPLAYERS];

int LastRequestManager::LRHandler(Menu* menu, MenuAction action, int param1, int param2)
{
	if (action == MenuAction_Select)
	{
		char info[4];
		menu->GetItem(param2, info, sizeof(info));
		LastRequest::Type type = LastRequest::Type::None;

		// TODO: Rewrite with std::string_view and lambda function init
		if (!strcmp(info, sCloseFightInfoStr))
			type = LastRequest::Type::CloseFight;
		else if (!strcmp(info, sShot4ShotInfoStr))
			type = LastRequest::Type::Shot4Shot;
		else if (!strcmp(info, sGunTossInfoStr))
			type = LastRequest::Type::GunToss;
		else if (!strcmp(info, sChickenFightInfoStr))
			type = LastRequest::Type::ChickenFight;
		else if (!strcmp(info, sNoscopeInfoStr))
			type = LastRequest::Type::Noscope;
		else if (!strcmp(info, sHotPotatoInfoStr))
			type = LastRequest::Type::HotPotato;
		else if (!strcmp(info, sDodgeBallInfoStr))
			type = LastRequest::Type::DodgeBall;
		else if (!strcmp(info, sRebelInfoStr))
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

void LastRequestManager::Unset(int loser, int winner)
{
	delete sActiveLastRequest;
	sActiveLastRequest = nullptr;
}

void LastRequestManager::TranslateLastRequestMainMenu(int client)
{
	Menu& menu = sLastRequestMainMenus[client - 1];
	menu.RemoveAllItems();
	menu.SetTitle("Last Request");
	menu.AddItem(sCloseFightInfoStr, "CloseFight");
	menu.AddItem(sShot4ShotInfoStr, "Shot4Shot");
	menu.AddItem(sGunTossInfoStr, "GunToss");
	menu.AddItem(sDodgeBallInfoStr, "DodgeBall");
	menu.AddItem(sNoscopeInfoStr, "NoscopeFight");
	menu.AddItem(sHotPotatoInfoStr, "HotPotato");
	menu.AddItem(sChickenFightInfoStr, "ChickenFight");
	menu.AddItem(sRebelInfoStr, "RebelFight");
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
