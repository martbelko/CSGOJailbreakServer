#pragma once

#include "smsdk_ext.h"

class MainPlugin
{
public:
	static void OnPluginStart();
	static void OnPluginEnd();

	static void OnRoundStartPre();
	static void OnRoundStartPost();

	static int CMDCallback(int client, char* command, char* args);

	// Client.inc
	static bool OnClientConnect(int client, char* rejectmsg, int maxlen);
	static void OnClientConnected(int client);
	static void OnClientPutInServer(int client);
	static void OnClientDisconnect(int client);
	static void OnClientDisconnectPost(int client);
	static int  OnClientCommand(int client, int args);
	static int  OnClientCommandKeyValues(int client, int kv); // TODO: KeyValues?
	static void OnClientCommandKeyValuesPost(int client, int kv); // TODO: KeyValues?
	static void OnClientSettingsChanged(int client);
	static void OnClientAuthorized(int client, const char* auth);
	static int  OnClientPreAdminCheck(int client);
	static void OnClientPostAdminFilter(int client);
	static void OnClientPostAdminCheck(int client);
};
