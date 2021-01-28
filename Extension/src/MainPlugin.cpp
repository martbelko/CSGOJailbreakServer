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

int MainPlugin::CMDCallback(int client, char* command, char* args)
{
	std::string r = std::string(command) + ' ' + std::string(args) + " %d";
	PublicManager::PrintToConsole(client, r.c_str(), 5);
	PublicManager::PrintToConsole(client, "Bye Bye");
	for (int i = 1; i <= PublicManager::GetMaxClients(); ++i)
	{
		if (PublicManager::IsClientInGame(i) && PublicManager::IsFakeClient(i))
			PublicManager::KickClient(i, "Bye BOTT");
	}

	return 0;
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

int MainPlugin::OnClientCommand(int client, int args)
{
	return 0;
}

int MainPlugin::OnClientCommandKeyValues(int client, int kv)
{
	return 0;
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

int MainPlugin::OnClientPreAdminCheck(int client)
{
	return 0;
}

void MainPlugin::OnClientPostAdminFilter(int client)
{

}

void MainPlugin::OnClientPostAdminCheck(int client)
{

}
