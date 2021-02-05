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

	// SDKTOOLS_HOOKS.INC
	/**
	 * @brief Called when a clients movement buttons are being processed
	 *
	 * @param client        Index of the client.
	 * @param buttons       Copyback buffer containing the current commands (as bitflags - see entity_prop_stocks.inc).
	 * @param impulse       Copyback buffer containing the current impulse command.
	 * @param vel           Players desired velocity.
	 * @param angles        Players desired view angles.
	 * @param weapon        Entity index of the new weapon if player switches weapon, 0 otherwise.
	 * @param subtype       Weapon subtype when selected from a menu.
	 * @param cmdnum        Command number. Increments from the first command sent.
	 * @param tickcount     Tick count. A client's prediction based on the server's GetGameTickCount value.
	 * @param seed          Random seed. Used to determine weapon recoil, spread, and other predicted elements.
	 * @param mouse         Mouse direction (x, y).
	 * @return              Plugin_Handled to block the commands from being processed, Plugin_Continue otherwise.
	 *
	 * @note To see if all 11 params are available, use FeatureType_Capability and FEATURECAP_PLAYERRUNCMD_11PARAMS.
	 */
	static Action OnPlayerRunCmd(int client, int& buttons, int& impulse, float vel[3], float angles[3], int& weapon, int& subtype, int& cmdnum, int& tickcount, int& seed, int mouse[2]);

	/**
	 * @brief Called after a clients movement buttons were processed.
	 *
	 * @param client        Index of the client.
	 * @param buttons       The current commands (as bitflags - see entity_prop_stocks.inc).
	 * @param impulse       The current impulse command.
	 * @param vel           Players desired velocity.
	 * @param angles        Players desired view angles.
	 * @param weapon        Entity index of the new weapon if player switches weapon, 0 otherwise.
	 * @param subtype       Weapon subtype when selected from a menu.
	 * @param cmdnum        Command number. Increments from the first command sent.
	 * @param tickcount     Tick count. A client's prediction based on the server's GetGameTickCount value.
	 * @param seed          Random seed. Used to determine weapon recoil, spread, and other predicted elements.
	 * @param mouse         Mouse direction (x, y).
	 */
	static void OnPlayerRunCmdPost(int client, int buttons, int impulse, const float vel[3], const float angles[3], int weapon, int subtype, int cmdnum, int tickcount, int seed, const int mouse[2]);

	/**
	 * @brief Called when a client requests a file from the server.
	 *
	 * @param client        Client index.
	 * @param sFile         Requested file path.
	 *
	 * @return              Plugin_Handled to block the transfer, Plugin_Continue to let it proceed.
	 */
	static Action OnFileSend(int client, const char* sFile);

	/**
	 * @brief Called when a client sends a file to the server.
	 *
	 * @param client        Client index.
	 * @param sFile         Requested file path.
	 *
	 * @return              Plugin_Handled to block the transfer, Plugin_Continue to let it proceed.
	 */
	static Action OnFileReceive(int client, const char* sFile);

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
