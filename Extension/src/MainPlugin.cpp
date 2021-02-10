#include "MainPlugin.h"

#include "PublicManager.h"

BasePlugin* MainPlugin::s_Plugin;

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
