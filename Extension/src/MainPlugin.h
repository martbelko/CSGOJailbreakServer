#pragma once

#include "smsdk_ext.h"

#include "Defines.h"

#include "PublicManager.h"

using PM = PublicManager;

class MainPlugin
{
public:
	static Action ConCmdCallback(int client, char* command, char* args);
	static Action SrvCmdCallback(char* command, char* args);
	static Action CmdListenerCallback(int client, char* command, int argc);

	static bool FilterClientsFunc(int entity, int contentsMask, void* data)
	{
		if (entity > PublicManager::GetMaxClients())
			return false;
		int caller = reinterpret_cast<int>(data);
		return caller != entity;
	}

	static bool LineGoesThroughSmoke(float from[3], float to[3])
	{
		static Address TheBots;
		static Handle CBotManager_IsLineBlockedBySmoke;
		static int OS = 0;
		if (OS == 0)
		{
			Handle hGameConf = PM::LoadGameConfigFile("LineGoesThroughSmoke.games");
			if (!hGameConf)
			{
				PM::SetFailState("Could not read LineGoesThroughSmoke.games.txt");
				return false;
			}

			OS = PM::GameConfGetOffset(hGameConf, "OS");

			TheBots = PM::GameConfGetAddress(hGameConf, "TheBots");
			if (!TheBots)
			{
				PM::CloseHandle(hGameConf);
				PM::SetFailState("TheBots == null");
				return false;
			}

			PM::StartPrepSDKCall(SDKCall_Raw);
			PM::PrepSDKCall_SetFromConf(hGameConf, SDKConf_Signature, "CBotManager::IsLineBlockedBySmoke");
			PM::PrepSDKCall_AddParameter(SDKType_Vector, SDKPass_Pointer);
			PM::PrepSDKCall_AddParameter(SDKType_Vector, SDKPass_Pointer);
			if (OS == 1)
				PM::PrepSDKCall_AddParameter(SDKType_Float, SDKPass_Plain);
			PM::PrepSDKCall_SetReturnInfo(SDKType_Bool, SDKPass_Plain);
			if (!(CBotManager_IsLineBlockedBySmoke = PM::EndPrepSDKCall()))
			{
				PM::CloseHandle(hGameConf);
				PM::SetFailState("Failed to get CBotManager::IsLineBlockedBySmoke function");
				return false;
			}

			PM::CloseHandle(hGameConf);
		}

		if (OS == 1)
			return PM::SDKCallSmoke4(CBotManager_IsLineBlockedBySmoke, TheBots, from, to, 1.0f);
		return PM::SDKCallSmoke3(CBotManager_IsLineBlockedBySmoke, TheBots, from, to);
	}

	// SOURCEMOD.INC

	static void OnPluginStart()
	{
		rootconsole->ConsolePrint("Plugin Start");

		PublicManager::HookEvent(MainPlugin::OnEventHookPre, "round_start", EventHookMode::EventHookMode_Pre);
		PublicManager::HookEvent(MainPlugin::OnEventHookPost, "round_start", EventHookMode::EventHookMode_Post);

		PublicManager::RegConsoleCmd("sm_test", "Testing...", 0);

		for (int i = 1; i <= PublicManager::GetMaxClients(); ++i)
			if (PublicManager::IsClientInGame(i))
				OnClientPutInServer(i);

		// PublicManager::SQL_TConnect(MainPlugin::OnSQLTConnectCallbackBanlist, "banlist", 0);
		// PublicManager::SQL_TConnect(MainPlugin::OnSQLTConnectCallbackDefault, "default", 0);
	}

	static APLRes AskPluginLoad2(Handle myself, bool late, char* error, int errMax)
	{
		return APLRes_Success;
	}

	static void OnPluginEnd()
	{
		rootconsole->ConsolePrint("Plugin End");
	}

	static void OnPluginPauseChange(bool pause)
	{

	}

	static void OnGameFrame()
	{

	}

	static void OnMapStart()
	{

	}

	static void OnMapEnd()
	{

	}

	static void OnConfigsExecuted()
	{

	}

	static void OnAutoConfigsBuffered()
	{

	}

	static void OnAllPluginsLoaded()
	{

	}

	static void OnLibraryAdded(const char* name)
	{

	}

	static void OnLibraryRemoved(const char* name)
	{

	}

	static bool OnClientFloodCheck(int client)
	{
		return false;
	}

	static void OnClientFloodResult(int client, bool blocked)
	{

	}

	// SDKTOOLS_VOICE.INC

	static void OnClientSpeaking(int client) {  }
	static void OnClientSpeakingEnd(int client) {  }

	// LOGGING.INC

	static Action OnLogAction(Handle source, Identity ident, int client, int target, const char* message)
	{
		return Plugin_Continue;
	}

	// TIMERS.INC

	static void OnMapTimeLeftChanged() {}

	// SDKTOOLS_HOOKS.INC

	static Action OnPlayerRunCmd(int client, int& buttons, int& impulse, float velocity[3],
		float angles[3], int& weapon, int& subtype, int& cmdnum, int& tickcount,
		int& seed, int mouse[2])
	{
		return Plugin_Continue;
	}

	static void OnPlayerRunCmdPost(int client, int buttons, int impulse, const float velocity[3],
		const float angles[3], int weapon, int subtype, int cmdnum, int tickcount,
		int seed, const int mouse[2])
	{
	}

	static Action OnFileSend(int client, const char* filepath)
	{
		return Plugin_Continue;
	}

	static Action OnFileReceive(int client, const char* filepath)
	{
		return Plugin_Continue;
	}

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
