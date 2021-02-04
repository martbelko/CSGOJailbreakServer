#pragma once

#include "smsdk_ext.h"

#include "Defines.h"

#include "PublicManager.h"

class MainPlugin
{
public:
	static void OnPluginStart();
	static void OnPluginEnd();

	static Action ConCmdCallback(int client, char* command, char* args);
	static Action SrvCmdCallback(char* command, char* args);
	static Action CmdListenerCallback(int client, char* command, int argc);

	// SDKHOOKS.INC
	static void OnEntityCreated(int entity, const char* classname);
	static void OnEntitySpawned(int entity, const char* classname);
	static void OnEntityDestroyed(int entity);
	static Action OnGetGameDescription(char gameDesc[64]);
	static Action OnLevelInit(const char* mapName, char mapEntities[2097152]);
	// callbacks
	static void SDKHookCallback1(int client) { }
	static Action SDKHookCallback2(int entity) { return Plugin_Continue; }
	static Action SDKHookCallback3(int entity, int other) { return Plugin_Continue; }
	static void SDKHookCallback4(int entity, int other) {}
	static Action SDKHookCallback5(int entity, int& maxhealth) { return Plugin_Continue; }
	static Action SDKHookCallback6(int victim, int& attacker, int& inflictor, float& damage, int& damagetype, int& weapon, float damageForce[3], float damagePosition[3], int damagecustom)
		{ return Plugin_Continue; }
	static void SDKHookCallback7(int victim, int attacker, int inflictor, float damage, int damagetype, int weapon, const float damageForce[3], const float damagePosition[3], int damagecustom)
		{ }
	static void SDKHookCallback8(int client, int shots, const char* weaponname) {}
	static Action SDKHookCallback9(int victim, int& attacker, int& inflictor, float& damage, int& damagetype, int& ammotype, int hitbox, int hitgroup)
	{
		return Plugin_Continue;
	}
	static void SDKHookCallback10(int victim, int attacker, int inflictor, float damage, int damagetype, int ammotype, int hitbox, int hitgroup) {}
	static bool SDKHookCallback11(int entity, int collisiongroup, int contentsmask, bool originalResult) { return true; }
	static Action SDKHookCallback12(int entity, int activator, int caller, UseType type, float value) { return Plugin_Continue; }
	static void SDKHookCallback13(int entity, int activator, int caller, UseType type, float value) { }
	static void SDKHookCallback14(int weapon, bool bSuccessful) {  }
	static bool SDKHookCallback15(int client, bool origRet) { return true; }

	// MENUS.INC
	static int TestMenuHandler(MenuHandle menu, MenuAction action, int param1, int param2)
	{
		rootconsole->ConsolePrint("Here LOL");
		return 0;
	}

	// EVENTS.INC
	static Action OnEventHookPre(EventHandle eventHandle, const char* name, bool dontBroadcast);
	static Action OnEventHookPost(EventHandle eventHandle, const char* name, bool dontBroadcast);

	// DBI.INC
	static void OnSQLTConnectCallbackBanlist(Handle owner, Handle hndl, const char* error, int data);
	static void OnSQLTConnectCallbackDefault(Handle owner, Handle hndl, const char* error, int data);
	static void OnSQLTQueryCallback(Handle owner, Handle hndl, const char* error, int data); // TODO: Unused

	// CSTRIKE.INC
	static Action CS_OnBuyCommand(int client, const char* weapon);
	static Action CS_OnCSWeaponDrop(int client, int weaponIndex);
	static Action CS_OnGetWeaponPrice(int client, const char* weapon, int& price);
	static Action CS_OnTerminateRound(float& delay, CSRoundEndReason& reason);

	// CONSOLE.INC
	static Action OnClientSayCommand(int client, char* command, char* args);
	static void OnClientSayCommandPost(int client, char* command, char* args);

	// CLIENT.INC
	static bool OnClientConnect(int client, char* rejectmsg, int maxlen);
	static void OnClientConnected(int client);
	static void OnClientPutInServer(int client)
	{
		PublicManager::SDKHook(client, SDKHookType::SDKHook_TraceAttack, MainPlugin::SDKHookCallback9);
	}
	static void OnClientDisconnect(int client);
	static void OnClientDisconnectPost(int client);
	static Action OnClientCommand(int client, int args);
	static Action OnClientCommandKeyValues(int client, KeyValuesHandle kv); // TODO: KeyValues?
	static void OnClientCommandKeyValuesPost(int client, KeyValuesHandle kv); // TODO: KeyValues?
	static void OnClientSettingsChanged(int client);
	static void OnClientAuthorized(int client, const char* auth);
	static Action  OnClientPreAdminCheck(int client);
	static void OnClientPostAdminFilter(int client);
	static void OnClientPostAdminCheck(int client);
};
