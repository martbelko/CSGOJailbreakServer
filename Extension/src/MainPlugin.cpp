#include "MainPlugin.h"

#include "PublicManager.h"

void MainPlugin::OnPluginStart()
{
	rootconsole->ConsolePrint("Plugin Start");

	PublicManager::HookEvent(MainPlugin::OnEventHookPre, "round_start", EventHookMode::EventHookMode_Pre);
	PublicManager::HookEvent(MainPlugin::OnEventHookPost, "round_start", EventHookMode::EventHookMode_Post);

	PublicManager::RegConsoleCmd("sm_test", "Testing...", 0);

	/*PublicManager::SQL_TConnect(MainPlugin::OnSQLTConnectCallbackBanlist, "banlist", 0);
	PublicManager::SQL_TConnect(MainPlugin::OnSQLTConnectCallbackDefault, "default", 0);*/
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

	MenuHandle menu = PublicManager::CreateMenu(TestMenuHandler, MENU_ACTIONS_DEFAULT);
	PublicManager::SetMenuTitle(menu, "Menu Title here");
	PublicManager::AddMenuItem(menu, "1", "Choice1", ITEMDRAW_DEFAULT);
	PublicManager::AddMenuItem(menu, "2", "Choice2", ITEMDRAW_DEFAULT);
	PublicManager::AddMenuItem(menu, "3", "Choice3", ITEMDRAW_DEFAULT);
	PublicManager::SetMenuExitButton(menu, false);
	PublicManager::DisplayMenu(menu, client + 1, 20);

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

void MainPlugin::OnClientPutInServer(int client)
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
