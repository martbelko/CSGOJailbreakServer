#pragma once

#include "smsdk_ext.h"

#include "Defines.h"

class MainPlugin
{
public:
	static void OnPluginStart();
	static void OnPluginEnd();

	static void OnRoundStartPre();
	static void OnRoundStartPost();

	static Action ConCmdCallback(int client, char* command, char* args);
	static Action SrvCmdCallback(char* command, char* args);
	static Action CmdListenerCallback(int client, char* command, int argc);

	// CSTRIKE.INC
	static Action CS_OnBuyCommand(int client, const char* weapon);
	static Action CS_OnCSWeaponDrop(int client, int weaponIndex);
	static Action CS_OnGetWeaponPrice(int client, const char* weapon, int& price);
	static Action CS_OnTerminateRound(float& delay, CSRoundEndReason& reason);

	// CONSOLE.INC
	static Action OnClientSayCommand(int client, char* command, char* args);
	static void OnClientSayCommandPost(int client, char* command, char* args);

	// CLIENT.inc
	static bool OnClientConnect(int client, char* rejectmsg, int maxlen);
	static void OnClientConnected(int client);
	static void OnClientPutInServer(int client);
	static void OnClientDisconnect(int client);
	static void OnClientDisconnectPost(int client);
	static Action OnClientCommand(int client, int args);
	static Action OnClientCommandKeyValues(int client, int kv); // TODO: KeyValues?
	static void OnClientCommandKeyValuesPost(int client, int kv); // TODO: KeyValues?
	static void OnClientSettingsChanged(int client);
	static void OnClientAuthorized(int client, const char* auth);
	static Action  OnClientPreAdminCheck(int client);
	static void OnClientPostAdminFilter(int client);
	static void OnClientPostAdminCheck(int client);
};
