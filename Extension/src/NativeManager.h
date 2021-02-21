#pragma once

#include "smsdk_ext.h"

#include "Defines.h"
#include "PublicManager.h"
#include "MainPlugin.h"

class NativeManager
{
public:
	// USERMESSAGES.INC

	//static int MsgHookCallback(UserMsg msgID, Handle msg, const int players[], int playersNum, bool reliable, bool init)
	static int MsgHookCallback(IPluginContext* pContext, const cell_t* params)
	{
		UserMsg msgID = params[1];
		Handle msg = params[2];

		int* players;
		pContext->LocalToPhysAddr(params[3], &players);

		int playersNum = params[4];
		bool reliable = params[5];
		bool init = params[6];

		MsgHookFunc callback = PublicManager::s_MsgHookCallbacks[msgID];
		return callback(msgID, msg, players, playersNum, reliable, init);
	}

	//static int MsgPostHookCallback(UserMsg msgID, bool sent)
	static int MsgPostHookCallback(IPluginContext* pContext, const cell_t* params)
	{
		UserMsg msgID = params[1];
		MsgPostHookFunc callback = PublicManager::s_MsgPostHookCallbacks[msgID];
		if (callback)
		{
			bool sent = params[2];
			callback(msgID, sent);
		}

		return 0;
	}

	// CONVARS.INC

	static int ConVarChangedCallback(IPluginContext* pContext, const cell_t* params)
	{
		ConVarHandle convar = params[1];
		char* oldValue;
		pContext->LocalToString(params[2], &oldValue);
		char* newValue;
		pContext->LocalToString(params[3], &newValue);

		ConVarChangedFunc callback = PublicManager::s_ConVarChangedCallbacks[convar];
		callback(convar, oldValue, newValue);
		return 0;
	}

	static int ConVarQueryFinishedCallback(IPluginContext* pContext, const cell_t* params)
	{
		QueryCookie cookie = static_cast<QueryCookie>(params[1]);
		int client = params[2];
		ConVarQueryResult result = static_cast<ConVarQueryResult>(params[3]);
		char* cvarName;
		pContext->LocalToString(params[4], &cvarName);
		char* cvarValue;
		pContext->LocalToString(params[5], &cvarValue);
		void* value = reinterpret_cast<void*>(params[6]);

		std::string cvarNameStr(cvarName);
		std::pair<int, std::string> pair = std::make_pair(client, cvarNameStr);
		ConVarQueryFinishedFunc callback = PublicManager::s_ConVarFinishedCallbacks[pair];
		callback(cookie, client, result, cvarName, cvarValue, value);
		return 0;
	}

	// SOURCEMOD.INC

	static int OnPluginStart(IPluginContext* pContext, const cell_t* params)
	{
		PublicManager::InitOnPluginStart(pContext);

		MainPlugin::OnPluginStart();
		return 0;
	}

	static int OnPluginEnd(IPluginContext* pContext, const cell_t* params)
	{
		MainPlugin::OnPluginEnd();
		return 0;
	}

	static int OnPluginPauseChange(IPluginContext* pContext, const cell_t* params)
	{
		bool pause = params[1];
		MainPlugin::OnPluginPauseChange(pause);
		return 0;
	}

	static int OnGameFrame(IPluginContext* pContext, const cell_t* params)
	{
		MainPlugin::OnGameFrame();
		return 0;
	}

	static int OnMapStart(IPluginContext* pContext, const cell_t* params)
	{
		MainPlugin::OnMapStart();
		return 0;
	}

	static int OnMapEnd(IPluginContext* pContext, const cell_t* params)
	{
		MainPlugin::OnMapEnd();
		return 0;
	}

	static int OnConfigsExecuted(IPluginContext* pContext, const cell_t* params)
	{
		MainPlugin::OnConfigsExecuted();
		return 0;
	}

	static int OnAutoConfigsBuffered(IPluginContext* pContext, const cell_t* params)
	{
		MainPlugin::OnAutoConfigsBuffered();
		return 0;
	}

	static int OnAllPluginsLoaded(IPluginContext* pContext, const cell_t* params)
	{
		MainPlugin::OnAllPluginsLoaded();
		return 0;
	}

	static int OnLibraryAdded(IPluginContext* pContext, const cell_t* params)
	{
		char* name;
		pContext->LocalToString(params[1], &name);
		MainPlugin::OnLibraryAdded(name);
		return 0;
	}

	static int OnLibraryRemoved(IPluginContext* pContext, const cell_t* params)
	{
		char* name;
		pContext->LocalToString(params[1], &name);
		MainPlugin::OnLibraryRemoved(name);
		return 0;
	}

	static int OnClientFloodCheck(IPluginContext* pContext, const cell_t* params)
	{
		int client = params[1];
		return MainPlugin::OnClientFloodCheck(client);
	}

	static int OnClientFloodResult(IPluginContext* pContext, const cell_t* params)
	{
		int client = params[1];
		bool blocked = params[2];
		MainPlugin::OnClientFloodResult(client, blocked);
		return 0;
	}

	// SDKTOOLS_SOUND.INC

	static int AmbientSHookCallback(IPluginContext* pContext, const cell_t* params)
	{
		char* sample;
		pContext->LocalToString(params[1], &sample);

		int* entityPtr;
		pContext->LocalToPhysAddr(params[2], &entityPtr);

		int* volumePtr;
		pContext->LocalToPhysAddr(params[3], &volumePtr);
		float volume = sp_ctof(*volumePtr);

		int* levelPtr;
		pContext->LocalToPhysAddr(params[4], &levelPtr);

		int* pitchPtr;
		pContext->LocalToPhysAddr(params[5], &pitchPtr);

		int* posPtr;
		pContext->LocalToPhysAddr(params[6], &posPtr);
		float pos[3] = { sp_ctof(posPtr[0]), sp_ctof(posPtr[1]), sp_ctof(posPtr[2]) };

		int* flagsPtr;
		pContext->LocalToPhysAddr(params[7], &flagsPtr);

		int* delayPtr;
		pContext->LocalToPhysAddr(params[8], &delayPtr);
		float delay = sp_ctof(*delayPtr);

		AmbientSHookFunc callback = PublicManager::s_AmbientSHookCallback;
		Action ret = callback(sample, *entityPtr, volume, *levelPtr, *pitchPtr, pos, *flagsPtr, delay);

		*delayPtr = delay;

		posPtr[0] = sp_ftoc(pos[0]);
		posPtr[1] = sp_ftoc(pos[1]);
		posPtr[2] = sp_ftoc(pos[2]);

		*volumePtr = sp_ftoc(volume);

		return ret;
	}

	static int NormalSHookCallback(IPluginContext* pContext, const cell_t* params)
	{
		int* clients;
		pContext->LocalToPhysAddr(params[1], &clients);

		int* numClientsPtr;
		pContext->LocalToPhysAddr(params[2], &numClientsPtr);

		char* sample;
		pContext->LocalToString(params[3], &sample);

		int* entityPtr;
		pContext->LocalToPhysAddr(params[4], &entityPtr);

		int* channelPtr;
		pContext->LocalToPhysAddr(params[5], &channelPtr);

		int* volumePtr;
		pContext->LocalToPhysAddr(params[6], &volumePtr);
		float volume = *volumePtr;

		int* levelPtr;
		pContext->LocalToPhysAddr(params[7], &levelPtr);

		int* pitchPtr;
		pContext->LocalToPhysAddr(params[8], &pitchPtr);

		int* flagsPtr;
		pContext->LocalToPhysAddr(params[9], &flagsPtr);

		char* soundEntry;
		pContext->LocalToString(params[10], &soundEntry);

		int* seedPtr;
		pContext->LocalToPhysAddr(params[11], &seedPtr);

		NormalSHookFunc callback = PublicManager::s_NormalSHookCallback;
		Action ret = callback(clients, *numClientsPtr, sample, *entityPtr, *channelPtr, volume, *levelPtr, *pitchPtr, *flagsPtr, soundEntry, *seedPtr);
		*volumePtr = volume;
		return ret;
	}

	// COMMANDFILTERS.INC

	static int MultiTargetFilterCallback(IPluginContext* pContext, const cell_t* params)
	{
		char* pattern;
		pContext->LocalToString(params[1], &pattern);
		Handle clients = params[2];

		std::string patternStr(pattern);
		MultiTargetFilterFunc callback = PublicManager::s_MultiTargetFilterCallbacks[patternStr];
		return callback(pattern, clients);
	}

	// SDKTOOLS_VOICE.INC

	static int OnClientSpeaking(IPluginContext* pContext, const cell_t* params)
	{
		int client = params[1];
		MainPlugin::OnClientSpeaking(client);
		return 0;
	}

	static int OnClientSpeakingEnd(IPluginContext* pContext, const cell_t* params)
	{
		int client = params[1];
		MainPlugin::OnClientSpeakingEnd(client);
		return 0;
	}

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

	static int OnPlayerRunCmd(IPluginContext* pContext, const cell_t* params)
	{
		int client = params[1];

		int* buttonsPtr;
		pContext->LocalToPhysAddr(params[2], &buttonsPtr);

		int* impulsePtr;
		pContext->LocalToPhysAddr(params[3], &impulsePtr);

		int* velocityPtr;
		pContext->LocalToPhysAddr(params[4], &velocityPtr);
		float velocity[3] = { sp_ctof(velocityPtr[0]), sp_ctof(velocityPtr[1]), sp_ctof(velocityPtr[2]) };

		int* anglesPtr;
		pContext->LocalToPhysAddr(params[5], &anglesPtr);
		float angles[3] = { sp_ctof(anglesPtr[0]), sp_ctof(anglesPtr[1]), sp_ctof(anglesPtr[2]) };

		int* weaponPtr;
		pContext->LocalToPhysAddr(params[6], &weaponPtr);

		int* subTypePtr;
		pContext->LocalToPhysAddr(params[7], &subTypePtr);

		int* cmdNumPtr;
		pContext->LocalToPhysAddr(params[8], &cmdNumPtr);

		int* tickCountPtr;
		pContext->LocalToPhysAddr(params[9], &tickCountPtr);

		int* seedPtr;
		pContext->LocalToPhysAddr(params[10], &seedPtr);

		int* mousePtr;
		pContext->LocalToPhysAddr(params[11], &mousePtr);

		Action res = MainPlugin::OnPlayerRunCmd(client, *buttonsPtr, *impulsePtr, velocity,
			angles, *weaponPtr, *subTypePtr, *cmdNumPtr, *tickCountPtr, *seedPtr, mousePtr);

		anglesPtr[0] = sp_ftoc(angles[0]);
		anglesPtr[1] = sp_ftoc(angles[1]);
		anglesPtr[2] = sp_ftoc(angles[2]);

		velocityPtr[0] = sp_ftoc(velocity[0]);
		velocityPtr[1] = sp_ftoc(velocity[1]);
		velocityPtr[2] = sp_ftoc(velocity[2]);

		return res;
	}

	static int OnPlayerRunCmdPost(IPluginContext* pContext, const cell_t* params)
	{
		int client = params[1];
		int buttons = params[2];
		int impulse = params[3];

		int* velocityPtr;
		pContext->LocalToPhysAddr(params[4], &velocityPtr);
		const float velocity[3] = { sp_ctof(velocityPtr[0]), sp_ctof(velocityPtr[1]), sp_ctof(velocityPtr[2]) };

		int* anglesPtr;
		pContext->LocalToPhysAddr(params[5], &anglesPtr);
		const float angles[3] = { sp_ctof(anglesPtr[0]), sp_ctof(anglesPtr[1]), sp_ctof(anglesPtr[2]) };

		int weapon = params[6];
		int subType = params[7];
		int cmdnum = params[8];
		int tickCount = params[9];
		int seed = params[10];

		int* mousePtr;
		pContext->LocalToPhysAddr(params[11], &mousePtr);

		MainPlugin::OnPlayerRunCmdPost(client, buttons, impulse, velocity, angles,
			weapon, subType, cmdnum, tickCount, seed, mousePtr);
		return 0;
	}

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

	// CONSOLE.INC

	static int OnClientSayCommand(IPluginContext* pContext, const cell_t* params);
	static int OnClientSayCommandPost(IPluginContext* pContext, const cell_t* params);

	static int ConCmdCallback(IPluginContext* pContext, const cell_t* params)
	{
		int client = params[1];
		int argc = params[2];

		char command[32];
		PublicManager::GetCmdArg(0, command, sizeof(command));
		std::string commandStr(command);
		ConCmdFunc callback = PublicManager::s_ConCmdCallbacks[commandStr];
		return callback(client, commandStr, argc);
	}

	static int SrvCmdCallback(IPluginContext* pContext, const cell_t* params)
	{
		int argc = params[1];

		char command[32];
		PublicManager::GetCmdArg(0, command, sizeof(command));
		std::string commandStr(command);
		SrvCmdFunc callback = PublicManager::s_SrvCmdCallbacks[commandStr];
		return callback(commandStr, argc);
	}

	static int CmdListenerCallback(IPluginContext* pContext, const cell_t* params)
	{
		int client = params[1];
		char* cmd;
		pContext->LocalToString(params[2], &cmd);
		int argc = params[3];

		std::string commandStr(cmd);
		CommandListenerFunc callback = PublicManager::s_CommandListenerCallbacks[commandStr];
		return callback(client, commandStr, argc);
	}


	// CLIENTS.INC

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
