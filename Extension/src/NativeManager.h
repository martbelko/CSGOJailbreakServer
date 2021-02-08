#pragma once

#include "smsdk_ext.h"

#include "Defines.h"
#include "PublicManager.h"
#include "MainPlugin.h"

class NativeManager
{
public:
	static cell_t OnPluginStart(IPluginContext* pContext, const cell_t* params);
	static cell_t OnPluginEnd(IPluginContext* pContext, const cell_t* params);

	static cell_t OnMapStart(IPluginContext* pContext, const cell_t* params);
	static cell_t OnMapEnd(IPluginContext* pContext, const cell_t* params);

	static cell_t ConCmdCallback(IPluginContext* pContext, const cell_t* params);
	static cell_t SrvCmdCallback(IPluginContext* pContext, const cell_t* params);
	static cell_t CmdListenerCallback(IPluginContext* pContext, const cell_t* params);

	// SDKTOOLS_TRACE.INC
	static int TraceEntityFilterCallback(IPluginContext* pContext, const cell_t* params)
	{
		int entity = params[1];
		int contentsMask = params[2];
		int filterIndex = params[3];

		TraceEntityFilterFunc callback = PublicManager::s_TraceEntityFilterCallbacks[filterIndex];
		void* data = PublicManager::s_TraceEntityFilterData[filterIndex];
		return callback(entity, contentsMask, data);
	}

	static int TraceEntityEnumeratorCallback(IPluginContext* pContext, const cell_t* params)
	{
		int entity = params[1];
		int enumeratorIndex = params[2];

		TraceEntityEnumeratorFunc callback = PublicManager::s_TraceEntityEnumeratorCallbacks[enumeratorIndex];
		void* data = PublicManager::s_TraceEntityEnumeratorData[enumeratorIndex];
		return callback(entity, data);
	}

	// LOGGING.INC
	static int OnLogAction(IPluginContext* pContext, const cell_t* params)
	{
		Handle handle = params[1];
		Identity ident = static_cast<Identity>(params[2]);
		int client = params[3];
		int target = params[4];
		char* message;
		pContext->LocalToString(params[5], &message);

		return MainPlugin::OnLogAction(handle, ident, client, target, message);
	}

	static int GameLogHookCallback(IPluginContext* pContext, const cell_t* params)
	{
		char* message;
		pContext->LocalToString(params[1], &message);
		return PublicManager::s_GameLogHookCallback(message);
	}

	// SDKTOOLS_TEMPENTS.INC
	static int TEHookCallback(IPluginContext* pContext, const cell_t* params)
	{
		char* teName;
		pContext->LocalToString(params[1], &teName);
		int* players;
		pContext->LocalToPhysAddr(params[2], &players);
		int numClients = params[3];
		float delay = sp_ctof(params[4]);

		std::string teNameStr = teName;
		TEHookFunc callback = PublicManager::s_TEHooksCallbacks[teNameStr];
		return callback(teName, players, numClients, delay);
	}

	// SDKTOOLS_ENTOUTPUT.INC
	static int EntityOutputCallback(IPluginContext* pContext, const cell_t* params)
	{
		char* output;
		pContext->LocalToString(params[1], &output);
		int caller = params[2];
		int activator = params[3];
		float delay = sp_ctof(params[4]);

		char className[64];
		PublicManager::GetEntityClassname(caller, className, sizeof(className));

		std::string classNameStr = className;
		std::string outputStr = output;
		EntityOutputFunc callback = PublicManager::s_EntityOutputCallbacks[std::make_pair(classNameStr, outputStr)];
		return callback(output, caller, activator, delay);
	}

	static int SingleEntityOutputCallback(IPluginContext* pContext, const cell_t* params)
	{
		char* output;
		pContext->LocalToString(params[1], &output);
		int caller = params[2];
		int activator = params[3];
		float delay = sp_ctof(params[4]);

		std::string outputStr = output;
		EntityOutputFunc callback = PublicManager::s_SingleEntityOutputCallbacks[std::make_pair(caller, outputStr)];
		return callback(output, caller, activator, delay);
	}

	// TIMERS.INC
	static int TimerCallback(IPluginContext* pContext, const cell_t* params)
	{
		Handle timer = params[1];
		void* data = reinterpret_cast<void*>(params[2]);
		TimerCallbackFunc callback = PublicManager::s_TimerCallbacks[timer];
		return callback(timer, data);
	}

	static int OnMapTimeLeftChanged(IPluginContext* pContext, const cell_t* params)
	{
		MainPlugin::OnMapTimeLeftChanged();
		return 0;
	}

	// SDKTOOLS_HOOKS.INC
	static int OnPlayerRunCmd(IPluginContext* pContext, const cell_t* params);
	static int OnPlayerRunCmdPost(IPluginContext* pContext, const cell_t* params);
	static int OnFileSend(IPluginContext* pContext, const cell_t* params);
	static int OnFileReceive(IPluginContext* pContext, const cell_t* params);

	// SDKHOOKS.INC
	static int OnEntityCreated(IPluginContext* pContext, const cell_t* params);
	static int OnEntitySpawned(IPluginContext* pContext, const cell_t* params);
	static int OnEntityDestroyed(IPluginContext* pContext, const cell_t* params);
	static int OnGetGameDescription(IPluginContext* pContext, const cell_t* params);
	static int OnLevelInit(IPluginContext* pContext, const cell_t* params);
	// callbacks
	static int SDKHooksEndTouch(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback3(SDKHookType::SDKHook_EndTouch, pContext, params); }
	static int SDKHooksFireBulletsPost(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback8(SDKHookType::SDKHook_FireBulletsPost, pContext, params); }
	static int SDKHooksOnTakeDamage(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback6(SDKHookType::SDKHook_OnTakeDamage, pContext, params); }
	static int SDKHooksOnTakeDamagePost(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback7(SDKHookType::SDKHook_OnTakeDamagePost, pContext, params); }
	static int SDKHooksPreThink(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback1(SDKHookType::SDKHook_PreThink, pContext, params); }
	static int SDKHooksPostThink(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback1(SDKHookType::SDKHook_PostThink, pContext, params); }
	static int SDKHooksSetTransmit(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback3(SDKHookType::SDKHook_SetTransmit, pContext, params); }
	static int SDKHooksSpawn(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback2(SDKHookType::SDKHook_Spawn, pContext, params); }
	static int SDKHooksStartTouch(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback3(SDKHookType::SDKHook_StartTouch, pContext, params); }
	static int SDKHooksThink(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback1(SDKHookType::SDKHook_Think, pContext, params); }
	static int SDKHooksTouch(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback3(SDKHookType::SDKHook_Touch, pContext, params); }
	static int SDKHooksTraceAttack(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback9(SDKHookType::SDKHook_TraceAttack, pContext, params); }
	static int SDKHooksTraceAttackPost(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback10(SDKHookType::SDKHook_TraceAttackPost, pContext, params); }
	static int SDKHooksWeaponCanSwitchTo(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback3(SDKHookType::SDKHook_WeaponCanSwitchTo, pContext, params); }
	static int SDKHooksWeaponCanUse(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback3(SDKHookType::SDKHook_WeaponCanUse, pContext, params); }
	static int SDKHooksWeaponDrop(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback3(SDKHookType::SDKHook_WeaponDrop, pContext, params); }
	static int SDKHooksWeaponEquip(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback3(SDKHookType::SDKHook_WeaponEquip, pContext, params); }
	static int SDKHooksWeaponSwitch(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback3(SDKHookType::SDKHook_WeaponSwitch, pContext, params); }
	static int SDKHooksShouldCollide(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback11(SDKHookType::SDKHook_ShouldCollide, pContext, params); }
	static int SDKHooksPreThinkPost(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback1(SDKHookType::SDKHook_PreThinkPost, pContext, params); }
	static int SDKHooksPostThinkPost(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback1(SDKHookType::SDKHook_PostThinkPost, pContext, params); }
	static int SDKHooksThinkPost(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback1(SDKHookType::SDKHook_ThinkPost, pContext, params); }
	static int SDKHooksEndTouchPost(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback4(SDKHookType::SDKHook_EndTouchPost, pContext, params); }
	static int SDKHooksGroundEntChanged(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback1(SDKHookType::SDKHook_GroundEntChangedPost, pContext, params); }
	static int SDKHooksSpawnPost(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback1(SDKHookType::SDKHook_SpawnPost, pContext, params); }
	static int SDKHooksStartTouchPost(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback4(SDKHookType::SDKHook_StartTouchPost, pContext, params); }
	static int SDKHooksTouchPost(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback4(SDKHookType::SDKHook_TouchPost, pContext, params); }
	static int SDKHooksVPhysicsUpdate(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback1(SDKHookType::SDKHook_VPhysicsUpdate, pContext, params); }
	static int SDKHooksVPhysicsUpdatePost(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback1(SDKHookType::SDKHook_VPhysicsUpdatePost, pContext, params); }
	static int SDKHooksWeaponCanSwitchToPost(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback4(SDKHookType::SDKHook_WeaponCanSwitchToPost, pContext, params); }
	static int SDKHooksWeaponCanUsePost(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback4(SDKHookType::SDKHook_WeaponCanUsePost, pContext, params); }
	static int SDKHooksWeaponDropPost(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback4(SDKHookType::SDKHook_WeaponDropPost, pContext, params); }
	static int SDKHooksWeaponEquipPost(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback4(SDKHookType::SDKHook_WeaponEquipPost, pContext, params); }
	static int SDKHooksWeaponSwitchPost(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback4(SDKHookType::SDKHook_WeaponSwitchPost, pContext, params); }
	static int SDKHooksUse(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback12(SDKHookType::SDKHook_Use, pContext, params); }
	static int SDKHooksUsePost(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback13(SDKHookType::SDKHook_UsePost, pContext, params); }
	static int SDKHooksReload(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback2(SDKHookType::SDKHook_Reload, pContext, params); }
	static int SDKHooksReloadPost(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback14(SDKHookType::SDKHook_ReloadPost, pContext, params); }
	static int SDKHooksGetMaxHealth(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback5(SDKHookType::SDKHook_GetMaxHealth, pContext, params); }
	static int SDKHooksBlocked(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback3(SDKHookType::SDKHook_Blocked, pContext, params); }
	static int SDKHooksBlockedPost(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback4(SDKHookType::SDKHook_BlockedPost, pContext, params); }
	static int SDKHooksOnTakeDamageAlive(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback6(SDKHookType::SDKHook_OnTakeDamageAlive, pContext, params); }
	static int SDKHooksOnTakeDamageAlivePost(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback7(SDKHookType::SDKHook_OnTakeDamageAlivePost, pContext, params); }
	static int SDKHooksCanBeAutobalanced(IPluginContext* pContext, const cell_t* params) { return SDKHooksCallback15(SDKHookType::SDKHook_CanBeAutobalanced, pContext, params); }
private:
	static int SDKHooksCallback1(SDKHookType type, IPluginContext* pContext, const cell_t* params);
	static int SDKHooksCallback2(SDKHookType type, IPluginContext* pContext, const cell_t* params);
	static int SDKHooksCallback3(SDKHookType type, IPluginContext* pContext, const cell_t* params);
	static int SDKHooksCallback4(SDKHookType type, IPluginContext* pContext, const cell_t* params);
	static int SDKHooksCallback5(SDKHookType type, IPluginContext* pContext, const cell_t* params);
	static int SDKHooksCallback6(SDKHookType type, IPluginContext* pContext, const cell_t* params);
	static int SDKHooksCallback7(SDKHookType type, IPluginContext* pContext, const cell_t* params);
	static int SDKHooksCallback8(SDKHookType type, IPluginContext* pContext, const cell_t* params);
	static int SDKHooksCallback9(SDKHookType type, IPluginContext* pContext, const cell_t* params);
	static int SDKHooksCallback10(SDKHookType type, IPluginContext* pContext, const cell_t* params);
	static int SDKHooksCallback11(SDKHookType type, IPluginContext* pContext, const cell_t* params);
	static int SDKHooksCallback12(SDKHookType type, IPluginContext* pContext, const cell_t* params);
	static int SDKHooksCallback13(SDKHookType type, IPluginContext* pContext, const cell_t* params);
	static int SDKHooksCallback14(SDKHookType type, IPluginContext* pContext, const cell_t* params);
	static int SDKHooksCallback15(SDKHookType type, IPluginContext* pContext, const cell_t* params);
public:
	// MENU.INC
	static int MenuHandlerCallback(IPluginContext* pContext, const cell_t* params);
	static int VoteHandlerCallback(IPluginContext* pContext, const cell_t* params);

	// EVENTS.INC
	static int EventHookCallbackPre(IPluginContext* pContext, const cell_t* params);
	static int EventHookCallbackPost(IPluginContext* pContext, const cell_t* params);
	static int EventHookCallbackPostNoCopy(IPluginContext* pContext, const cell_t* params);

	// DBI.INC
	static int SQLTxnSuccessCallback(IPluginContext* pContext, const cell_t* params);
	static int SQLTxnFailureCallback(IPluginContext* pContext, const cell_t* params);
	static int SQLTCallbackConnect(IPluginContext* pContext, const cell_t* params);
	static int SQLTCallbackQuery(IPluginContext* pContext, const cell_t* params);

	// CSTRIKE.INC
	static int CS_OnBuyCommand(IPluginContext* pContext, const cell_t* params);
	static int CS_OnCSWeaponDrop(IPluginContext* pContext, const cell_t* params);
	static int CS_OnGetWeaponPrice(IPluginContext* pContext, const cell_t* params);
	static int CS_OnTerminateRound(IPluginContext* pContext, const cell_t* params);

	// CONSOLE.inc
	static int OnClientSayCommand(IPluginContext* pContext, const cell_t* params);
	static int OnClientSayCommandPost(IPluginContext* pContext, const cell_t* params);

	// CLIENTS.inc
	static int OnClientConnect(IPluginContext* pContext, const cell_t* params);
	static int OnClientConnected(IPluginContext* pContext, const cell_t* params);
	static int OnClientPutInServer(IPluginContext* pContext, const cell_t* params);
	static int OnClientDisconnect(IPluginContext* pContext, const cell_t* params);
	static int OnClientDisconnectPost(IPluginContext* pContext, const cell_t* params);
	static int OnClientCommand(IPluginContext* pContext, const cell_t* params);
	static int OnClientCommandKeyValues(IPluginContext* pContext, const cell_t* params);
	static int OnClientCommandKeyValuesPost(IPluginContext* pContext, const cell_t* params);
	static int OnClientSettingsChanged(IPluginContext* pContext, const cell_t* params);
	static int OnClientAuthorized(IPluginContext* pContext, const cell_t* params);
	static int OnClientPreAdminCheck(IPluginContext* pContext, const cell_t* params);
	static int OnClientPostAdminFilter(IPluginContext* pContext, const cell_t* params);
	static int OnClientPostAdminCheck(IPluginContext* pContext, const cell_t* params);
};
