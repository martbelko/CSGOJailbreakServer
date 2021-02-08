#include "MainPlugin.h"

#include "PublicManager.h"

using PM = PublicManager;

void MainPlugin::OnPluginStart()
{
	rootconsole->ConsolePrint("Plugin Start");

	PM::HookEvent(MainPlugin::OnEventHookPre, "round_start", EventHookMode::EventHookMode_Pre);
	PM::HookEvent(MainPlugin::OnEventHookPost, "round_start", EventHookMode::EventHookMode_Post);

	PM::RegConsoleCmd("sm_test", "Testing...", 0);

	for (int i = 1; i <= PM::GetMaxClients(); ++i)
		if (PM::IsClientInGame(i))
			OnClientPutInServer(i);

	// PM::SQL_TConnect(MainPlugin::OnSQLTConnectCallbackBanlist, "banlist", 0);
	// PM::SQL_TConnect(MainPlugin::OnSQLTConnectCallbackDefault, "default", 0);
}

void MainPlugin::OnPluginEnd()
{
	rootconsole->ConsolePrint("Plugin End");
}

Action MainPlugin::ConCmdCallback(int client, char* command, char* args)
{
	/*std::string r = "%d %d %d %N %s %s %f %f";
	int x = 5;
	int y = 6;
	int z = 8;
	float w = 61.49f;
	float w2 = 0.01f;
	PublicManager::PrintToConsole(client + 1, r.c_str(), x, y, z, client, "LOL", "WTF", 58.0f, w + 1);
	PublicManager::PrintToConsole(client + 1, "Bye Bye");
	float v[3] = { 0, 0, 0 };
	PublicManager::GetClientAbsOrigin(client + 1, v);
	PublicManager::PrintToConsole(client + 1, "%f, %f, %f", v[0], v[1], v[2]);
	for (int i = 1; i <= PublicManager::GetMaxClients(); ++i)
	{
		if (PublicManager::IsClientInGame(i) && PublicManager::IsFakeClient(i))
			PublicManager::KickClient(i, "Bye BOTT");
	}

	PublicManager::ReplyToCommand(client, "LOL YOU NOOB %d", 10);
	PublicManager::FakeClientCommand(client + 1, "say WTF %s", "ALL");
	PublicManager::FakeClientCommand(client + 1, "say_team WTF %s", "TEAM");
	PublicManager::CS_RespawnPlayer(client + 1);*/

	++client;
	float pos[3];
	PM::GetClientEyePosition(client, pos);
	float angles[3];
	PM::GetClientEyeAngles(client, angles);

	Handle trace = PM::TR_TraceRayFilterEx(pos, angles, MASK_SHOT, RayType::RayType_Infinite, FilterClientsFunc, reinterpret_cast<void*>(client));
	if (PM::TR_DidHit(trace))
	{
		int hitClient = PM::TR_GetEntityIndex(trace);
		rootconsole->ConsolePrint("Hit %d", hitClient);
		if (hitClient > 0 && hitClient <= PM::GetMaxClients() && PM::IsClientInGame(hitClient))
		{
			char name[MAX_NAME_LENGTH];
			PM::GetClientName(hitClient, name, sizeof(name));
			PM::PrintToChatAll(name);
		}
	}

	PM::CloseHandle(trace);

	/*float origin[3];
	PM::GetClientAbsOrigin(client + 1, origin);
	int* clients = new int[PM::GetMaxClients()];
	PM::GetClientsInRange(origin, ClientRangeType::RangeType_Audibility, clients, PM::GetMaxClients());

	for (int i = 0; i < PM::GetMaxClients(); ++i)
	{
		int c = clients[i];
		if (c > 0 && c <= PM::GetMaxClients() && PM::IsClientInGame(c))
		{
			char name[MAX_PLAYER_NAME_LENGTH];
			PM::GetClientName(c, name, sizeof(name));
			rootconsole->ConsolePrint(name);
		}
	}

	delete[] clients;

	PublicManager::SetClientName(client + 1, "LOOLUNOOB");
	PublicManager::ForcePlayerSuicide(client + 2);
	PublicManager::IgniteEntity(client + 1, 5.0f);
	PublicManager::SlapPlayer(client + 1, 20);

	PublicManager::SetEntityHealth(client + 1, 300);

	char className[64];
	PublicManager::GetEdictClassname(client + 1, className, sizeof(className));
	rootconsole->ConsolePrint("Class Name: %s", className);

	char weapon[64];
	PublicManager::GetClientWeapon(client + 1, weapon, sizeof(weapon));
	rootconsole->ConsolePrint("Weapon: %s", weapon);

	PublicManager::CS_SetClientClanTag(client + 1, "LOL");

	char clanTag[32];
	PublicManager::CS_GetClientClanTag(client + 1, clanTag, sizeof(clanTag));
	rootconsole->ConsolePrint("Clan: %s", clanTag);

	MenuHandle menu = PublicManager::CreateMenu(TestMenuHandler, MENU_ACTIONS_DEFAULT);
	PublicManager::SetMenuTitle(menu, "Menu Title here");
	PublicManager::AddMenuItem(menu, "1", "Choice1", ITEMDRAW_DEFAULT);
	PublicManager::AddMenuItem(menu, "2", "Choice2", ITEMDRAW_DEFAULT);
	PublicManager::AddMenuItem(menu, "3", "Choice3", ITEMDRAW_DEFAULT);
	PublicManager::SetMenuExitButton(menu, false);
	PublicManager::DisplayMenu(menu, client + 1, 20);

	rootconsole->ConsolePrint("Sizeof(KeyValues) = %d", sizeof(KeyValues));*/

	return Plugin_Handled;
}

Action MainPlugin::SrvCmdCallback(char* command, char* args)
{
	return Plugin_Handled;
}

Action MainPlugin::CmdListenerCallback(int client, char* command, int argc)
{
	return Plugin_Handled;
}

void MainPlugin::OnEntityCreated(int entity, const char* classname)
{

}

void MainPlugin::OnEntitySpawned(int entity, const char* classname)
{

}

void MainPlugin::OnEntityDestroyed(int entity)
{

}

Action MainPlugin::OnGetGameDescription(char gameDesc[64])
{
	rootconsole->ConsolePrint("Game Desc: %s", gameDesc);
	return Plugin_Continue;
}

Action MainPlugin::OnLevelInit(const char* mapName, char mapEntities[2097152])
{
	return Plugin_Continue;
}

Action MainPlugin::OnEventHookPre(EventHandle eventHandle, const char* name, bool dontBroadcast)
{
	rootconsole->ConsolePrint("Event PRE: %s", name);
	return Plugin_Continue;
}

Action MainPlugin::OnEventHookPost(EventHandle eventHandle, const char* name, bool dontBroadcast)
{
	rootconsole->ConsolePrint("Event POST: %s", name);
	return Plugin_Continue;
}

void MainPlugin::OnSQLTConnectCallbackBanlist(Handle owner, Handle hndl, const char* error, int data)
{
	rootconsole->ConsolePrint("Connected to BanList %d", hndl);
	if (hndl == INVALID_HANDLE)
		PublicManager::PrintToServer("Failed to connect to Banlist database: ERROR: %s", (const char*)error);
	else
		PublicManager::PrintToServer("Connection to Banlist successful");
}

void MainPlugin::OnSQLTConnectCallbackDefault(Handle owner, Handle hndl, const char* error, int data)
{
	rootconsole->ConsolePrint("Connected to Default %d", hndl);
	if (hndl == INVALID_HANDLE)
		PublicManager::PrintToServer("Failed to connect to Default database: ERROR: %s", (const char*)error);
	else
		PublicManager::PrintToServer("Connection to Default successful");
}

void MainPlugin::OnSQLTQueryCallback(Handle owner, Handle hndl, const char* error, int data)
{

}

Action MainPlugin::CS_OnBuyCommand(int client, const char* weapon)
{
	rootconsole->ConsolePrint("BuyCommand");
	return Plugin_Continue;
}

Action MainPlugin::CS_OnCSWeaponDrop(int client, int weaponIndex)
{
	rootconsole->ConsolePrint("WeaponDrop");
	return Plugin_Continue;
}

Action MainPlugin::CS_OnGetWeaponPrice(int client, const char* weapon, int& price)
{
	rootconsole->ConsolePrint("GetWeaponPrice");
	return Plugin_Continue;
}

Action MainPlugin::CS_OnTerminateRound(float& delay, CSRoundEndReason& reason)
{
	rootconsole->ConsolePrint("TerminateRound");
	return Plugin_Continue;
}

Action MainPlugin::OnClientSayCommand(int client, char* command, char* args)
{
	return Plugin_Continue;
}

void MainPlugin::OnClientSayCommandPost(int client, char* command, char* args)
{

}

bool MainPlugin::OnClientConnect(int client, char* rejectmsg, int maxlen)
{
	return true;
}

void MainPlugin::OnClientConnected(int client)
{

}

void MainPlugin::OnClientDisconnect(int client)
{

}

void MainPlugin::OnClientDisconnectPost(int client)
{

}

Action MainPlugin::OnClientCommand(int client, int args)
{
	return Plugin_Continue;
}

Action MainPlugin::OnClientCommandKeyValues(int client, KeyValuesHandle kv)
{
	return Plugin_Continue;
}

void MainPlugin::OnClientCommandKeyValuesPost(int client, KeyValuesHandle kv)
{

}

void MainPlugin::OnClientSettingsChanged(int client)
{

}

void MainPlugin::OnClientAuthorized(int client, const char* auth)
{

}

Action MainPlugin::OnClientPreAdminCheck(int client)
{
	return Plugin_Continue;
}

void MainPlugin::OnClientPostAdminFilter(int client)
{

}

void MainPlugin::OnClientPostAdminCheck(int client)
{

}
