#include "MainPlugin.h"

#include "PublicManager.h"

void MainPlugin::OnPluginStart()
{
	rootconsole->ConsolePrint("Plugin Start");
	PublicManager::RegConsoleCmd("sm_test", "Testing...", 0);
}

void MainPlugin::OnPluginEnd()
{
	rootconsole->ConsolePrint("Plugin End");
}

void MainPlugin::OnRoundStartPre()
{
	rootconsole->ConsolePrint("Round Start Pre");
}

void MainPlugin::OnRoundStartPost()
{
	rootconsole->ConsolePrint("Round Start Post");
}

Action MainPlugin::ConCmdCallback(int client, char* command, char* args)
{
	std::string r = "%d %d %d %N %s %s %f %f";
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
	PublicManager::CS_RespawnPlayer(client + 1);

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

Action MainPlugin::OnClientCommandKeyValues(int client, int kv)
{
	return Plugin_Continue;
}

void MainPlugin::OnClientCommandKeyValuesPost(int client, int kv)
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
