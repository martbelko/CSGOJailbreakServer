#pragma once

#include "smsdk_ext.h"

#include "Defines.h"
#include "PublicManager.h"
#include "BasePlugin.h"

#include "Common/Logging/Log.h"

extern BasePlugin* GetPlugin();

class MainPlugin
{
public:
	// SOURCEMOD.INC

	static void OnPluginStart()
	{
		Log::Init();

		s_Plugin = GetPlugin();
		s_Plugin->OnPluginStart();
	}

	static void OnPluginEnd()
	{
		s_Plugin->OnPluginEnd();
	}

	static void OnPluginPauseChange(bool pause)
	{
		s_Plugin->OnPluginPauseChange(pause);
	}

	static void OnGameFrame()
	{
		s_Plugin->OnGameFrame();
	}

	static void OnMapStart()
	{
		s_Plugin->OnMapStart();
	}

	static void OnMapEnd()
	{
		s_Plugin->OnMapEnd();
	}

	static void OnConfigsExecuted()
	{
		s_Plugin->OnConfigsExecuted();
	}

	static void OnAutoConfigsBuffered()
	{
		s_Plugin->OnAutoConfigsBuffered();
	}

	static void OnAllPluginsLoaded()
	{
		s_Plugin->OnAllPluginsLoaded();
	}

	static void OnLibraryAdded(const char* name)
	{
		s_Plugin->OnLibraryAdded(name);
	}

	static void OnLibraryRemoved(const char* name)
	{
		s_Plugin->OnLibraryRemoved(name);
	}

	static bool OnClientFloodCheck(int client)
	{
		return s_Plugin->OnClientFloodCheck(client);
	}

	static void OnClientFloodResult(int client, bool blocked)
	{
		s_Plugin->OnClientFloodResult(client, blocked);
	}

	// SDKTOOLS_VOICE.INC

	static void OnClientSpeaking(int client)
	{
		s_Plugin->OnClientSpeaking(client);
	}

	static void OnClientSpeakingEnd(int client)
	{
		s_Plugin->OnClientSpeakingEnd(client);
	}

	// LOGGING.INC

	static Action OnLogAction(Handle source, Identity ident, int client, int target, const char* message)
	{
		return s_Plugin->OnLogAction(source, ident, client, target, message);
	}

	// TIMERS.INC

	static void OnMapTimeLeftChanged()
	{
		s_Plugin->OnMapTimeLeftChanged();
	}

	// SDKTOOLS_HOOKS.INC

	static Action OnPlayerRunCmd(int client, int& buttons, int& impulse, float velocity[3],
		float angles[3], int& weapon, int& subtype, int& cmdnum, int& tickcount,
		int& seed, int mouse[2])
	{
		return s_Plugin->OnPlayerRunCmd(client, buttons, impulse, velocity, angles, weapon, subtype, cmdnum, tickcount, seed, mouse);
	}

	static void OnPlayerRunCmdPost(int client, int buttons, int impulse, const float velocity[3],
		const float angles[3], int weapon, int subtype, int cmdnum, int tickcount,
		int seed, const int mouse[2])
	{
		s_Plugin->OnPlayerRunCmdPost(client, buttons, impulse, velocity, angles, weapon, subtype, cmdnum, tickcount, seed, mouse);
	}

	// SDKHOOKS.INC

	static void OnEntityCreated(int entity, const char* classname)
	{
		s_Plugin->OnEntityCreated(entity, classname);
	}

	static void OnEntitySpawned(int entity, const char* classname)
	{
		s_Plugin->OnEntitySpawned(entity, classname);
	}

	static void OnEntityDestroyed(int entity)
	{
		s_Plugin->OnEntityDestroyed(entity);
	}

	static Action OnGetGameDescription(char gameDesc[64])
	{
		return s_Plugin->OnGetGameDescription(gameDesc);
	}

	static Action OnLevelInit(const char* mapName, char mapEntities[2097152])
	{
		return s_Plugin->OnLevelInit(mapName, mapEntities);
	}

	// CSTRIKE.INC

	static Action CS_OnBuyCommand(int client, const char* weapon)
	{
		return s_Plugin->CS_OnBuyCommand(client, weapon);
	}

	static Action CS_OnCSWeaponDrop(int client, int weaponIndex)
	{
		return s_Plugin->CS_OnCSWeaponDrop(client, weaponIndex);
	}

	static Action CS_OnGetWeaponPrice(int client, const char* weapon, int& price)
	{
		return s_Plugin->CS_OnGetWeaponPrice(client, weapon, price);
	}

	static Action CS_OnTerminateRound(float& delay, CSRoundEndReason& reason)
	{
		return s_Plugin->CS_OnTerminateRound(delay, reason);
	}

	// CONSOLE.INC

	static Action OnClientSayCommand(int client, char* command, char* args)
	{
		return s_Plugin->OnClientSayCommand(client, command, args);
	}

	static void OnClientSayCommandPost(int client, char* command, char* args)
	{
		s_Plugin->OnClientSayCommandPost(client, command, args);
	}

	// CLIENT.INC

	static bool OnClientConnect(int client, char* rejectmsg, int maxlen)
	{
		return s_Plugin->OnClientConnect(client, rejectmsg, maxlen);
	}

	static void OnClientConnected(int client)
	{
		s_Plugin->OnClientConnected(client);
	}

	static void OnClientPutInServer(int client)
	{
		s_Plugin->OnClientPutInServer(client);
	}

	static void OnClientDisconnect(int client)
	{
		s_Plugin->OnClientDisconnect(client);
	}

	static void OnClientDisconnectPost(int client)
	{
		s_Plugin->OnClientDisconnectPost(client);
	}

	static Action OnClientCommand(int client, int args)
	{
		return s_Plugin->OnClientCommand(client, args);
	}

	static Action OnClientCommandKeyValues(int client, KeyValuesHandle kv)
	{
		return s_Plugin->OnClientCommandKeyValues(client, kv);
	}

	static void OnClientCommandKeyValuesPost(int client, KeyValuesHandle kv)
	{
		s_Plugin->OnClientCommandKeyValuesPost(client, kv);
	}

	static void OnClientSettingsChanged(int client)
	{
		s_Plugin->OnClientSettingsChanged(client);
	}

	static void OnClientAuthorized(int client, const char* auth)
	{
		s_Plugin->OnClientAuthorized(client, auth);
	}

	static Action  OnClientPreAdminCheck(int client)
	{
		return s_Plugin->OnClientPreAdminCheck(client);
	}

	static void OnClientPostAdminFilter(int client)
	{
		s_Plugin->OnClientPostAdminFilter(client);
	}

	static void OnClientPostAdminCheck(int client)
	{
		s_Plugin->OnClientPostAdminCheck(client);
	}
private:
	static BasePlugin* s_Plugin;
};
