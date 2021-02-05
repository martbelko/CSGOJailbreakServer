#pragma once

#include "smsdk_ext.h"

#include "Defines.h"

#include <sstream>
#include <unordered_map>

#define VARIADIC_FUNC2(FUNC, FUNC_IMPL, T1) \
	static void FUNC(T1 arg1) { PushArg(FUNC_IMPL, arg1); ExecFunc(FUNC_IMPL); } \
	template<typename ... Args> \
	static void FUNC(T1 arg1, Args ... args) { PushArg(FUNC_IMPL, arg1); FUNC##Sub(args...); } \
	private: \
	template<typename P1, typename ... Args> \
	static void FUNC##Sub(P1 p1, Args ... args) { PushArgRef(FUNC_IMPL, p1); FUNC##Sub(args...); } \
	static void FUNC##Sub(int& arg) { PushArgRef(FUNC_IMPL, arg); ExecFunc(FUNC_IMPL); } \
	static void FUNC##Sub(float& arg) { PushArgRef(FUNC_IMPL, arg); ExecFunc(FUNC_IMPL); } \
	static void FUNC##Sub(const char* arg) { PushArg(FUNC_IMPL, arg); ExecFunc(FUNC_IMPL); } \
	public:

#define VARIADIC_FUNC3(FUNC, FUNC_IMPL, T1, T2) \
	static void FUNC(T1 arg1, T2 arg2) { PushArg(FUNC_IMPL, arg1); PushArg(FUNC_IMPL, arg2); ExecFunc(FUNC_IMPL); } \
	template<typename ... Args> \
	static void FUNC(T1 arg1, T2 arg2, Args ... args) { PushArg(FUNC_IMPL, arg1); PushArg(FUNC_IMPL, arg2); FUNC##Sub(args...); } \
	private: \
	template<typename P1, typename ... Args> \
	static void FUNC##Sub(P1 p1, Args ... args) { PushArgRef(FUNC_IMPL, p1); FUNC##Sub(args...); } \
	static void FUNC##Sub(int& arg) { PushArgRef(FUNC_IMPL, arg); ExecFunc(FUNC_IMPL); } \
	static void FUNC##Sub(float& arg) { PushArgRef(FUNC_IMPL, arg); ExecFunc(FUNC_IMPL); } \
	static void FUNC##Sub(const char* arg) { PushArg(FUNC_IMPL, arg); ExecFunc(FUNC_IMPL); } \
	public:

#define VARIADIC_FUNC4(FUNC, FUNC_IMPL, T1, T2, T3) \
	static void FUNC(T1 arg1, T2 arg2, T3 arg3) { PushArg(FUNC_IMPL, arg1); PushArg(FUNC_IMPL, arg2); PushArg(FUNC_IMPL, arg3); ExecFunc(FUNC_IMPL); } \
	template<typename ... Args> \
	static void FUNC(T1 arg1, T2 arg2, T3 arg3, Args ... args) { PushArg(FUNC_IMPL, arg1); PushArg(FUNC_IMPL, arg2); PushArg(FUNC_IMPL, arg3); FUNC##Sub(args...); } \
	private: \
	template<typename P1, typename ... Args> \
	static void FUNC##Sub(P1 p1, Args ... args) { PushArgRef(FUNC_IMPL, p1); FUNC##Sub(args...); } \
	static void FUNC##Sub(int& arg) { PushArgRef(FUNC_IMPL, arg); ExecFunc(FUNC_IMPL); } \
	static void FUNC##Sub(float& arg) { PushArgRef(FUNC_IMPL, arg); ExecFunc(FUNC_IMPL); } \
	static void FUNC##Sub(const char* arg) { PushArg(FUNC_IMPL, arg); ExecFunc(FUNC_IMPL); } \
	public:

#define VARIADIC_FUNC5(FUNC, FUNC_IMPL, T1, T2, T3, T4) \
	static void FUNC(T1 client, T2 message, T3 arg3, T4 arg4) { PushArg(FUNC_IMPL, client); PushArg(FUNC_IMPL, message); PushArg(FUNC_IMPL, arg3); PushArg(FUNC_IMPL, arg4); ExecFunc(FUNC_IMPL); } \
	template<typename ... Args> \
	static void FUNC(T1 client, T2 format, T3 arg3, T4 arg4, Args ... args) { PushArg(FUNC_IMPL, client); PushArg(FUNC_IMPL, format); PushArg(FUNC_IMPL, arg3); PushArg(FUNC_IMPL, arg4); FUNC##Sub(args...); } \
	private: \
	template<typename P1, typename ... Args> \
	static void FUNC##Sub(P1 p1, Args ... args) { PushArgRef(FUNC_IMPL, p1); FUNC##Sub(args...); } \
	static void FUNC##Sub(int& arg) { PushArgRef(FUNC_IMPL, arg); ExecFunc(FUNC_IMPL); } \
	static void FUNC##Sub(float& arg) { PushArgRef(FUNC_IMPL, arg); ExecFunc(FUNC_IMPL); } \
	static void FUNC##Sub(const char* arg) { PushArg(FUNC_IMPL, arg); ExecFunc(FUNC_IMPL); } \
	public:

// PreThink/Post - client
// PostThink/Post - client
// GroundEntChanged - entity
// SpawnPost - entity
// Think/Post - entity
// VPhysicsUpdate/Post - entity
using SDKHooksCallback1Func = void(*)(int client);

// Spawn - entity
// Reload - weapon
using SDKHooksCallback2Func = Action(*)(int entity);

// EndTouch - entity, other
// StartTouch - entity, other
// Touch - entity, other
// Blocked - entity, other
// SetTransmit - entity, client
// WeaponCanSwitchTo - client, weapon
// WeaponCanUse - client, weapon
// WeaponDrop - client, weapon
// WeaponEquip - client, weapon
// WeaponSwitch - client, weapon
using SDKHooksCallback3Func = Action(*)(int entity, int other);

// EndTouchPost - entity, other
// StartTouchPost - entity, other
// TouchPost - entity, other
// BlockedPost - entity, other
// WeaponCanSwitchToPost - client, weapon
// WeaponCanUsePost - client, weapon
// WeaponDropPost - client, weapon
// WeaponEquipPost - client, weapon
// WeaponSwitchPost - client, weapon
using SDKHooksCallback4Func = void(*)(int entity, int other);

// GetMaxHealth (ep2v and later)
using SDKHooksCallback5Func = Action(*)(int entity, int& maxhealth);

// OnTakeDamage
// OnTakeDamageAlive
// Note: The weapon parameter is not used by all games and damage sources.
// Note: Force application is dependent on game and damage type(s)
// SDKHooks 2.1+  (can check for support at runtime using GetFeatureStatus on SDKHook_DmgCustomInOTD capability.
// DON'T attempt to access 'damagecustom' var if feature status != available
using SDKHooksCallback6Func = Action(*)(int victim, int& attacker, int& inflictor, float& damage, int& damagetype, int& weapon, float damageForce[3], float damagePosition[3], int damagecustom);

// OnTakeDamagePost
// OnTakeDamageAlivePost
using SDKHooksCallback7Func = void(*)(int victim, int attacker, int inflictor, float damage, int damagetype, int weapon, const float damageForce[3], const float damagePosition[3], int damagecustom);

// FireBulletsPost
using SDKHooksCallback8Func = void(*)(int client, int shots, const char* weaponname);

// TraceAttack
using SDKHooksCallback9Func = Action(*)(int victim, int& attacker, int& inflictor, float& damage, int& damagetype, int& ammotype, int hitbox, int hitgroup);

// TraceAttackPost
using SDKHooksCallback10Func = void(*)(int victim, int attacker, int inflictor, float damage, int damagetype, int ammotype, int hitbox, int hitgroup);

// ShouldCollide
using SDKHooksCallback11Func = bool(*)(int entity, int collisiongroup, int contentsmask, bool originalResult);

// Use
using SDKHooksCallback12Func = Action(*)(int entity, int activator, int caller, UseType type, float value);

// UsePost
using SDKHooksCallback13Func = void(*)(int entity, int activator, int caller, UseType type, float value);

// Reload post
using SDKHooksCallback14Func = void(*)(int weapon, bool bSuccessful);

// CanBeAutobalanced
using SDKHooksCallback15Func = bool(*)(int client, bool origRet);

using SQLTxnSuccessFunc = void (*)(database_t db, int data, int numQueries, DBResultSet results[], int queryData[]);
using SQLTxnFailureFunc = void(*)(database_t db, int data, int numQueries, const char* error, int failIndex, int queryData[]);
using SQLTCallbackFunc = void(*)(Handle owner, Handle hndl, const char* error, int data);
using EventHookCallback = Action(*)(EventHandle eventHandle, const char* name, bool dontBroadcast);
using MenuHandler = int(*)(MenuHandle menu, MenuAction action, int param1, int param2);
using VoteHandler = void(*)(MenuHandle menu, int numVotes, int numClients, const int** clientInfo, int numItems, const int** itemInfo);

struct pair_hash
{
	template <class T1, class T2>
	std::size_t operator()(const std::pair<T1, T2>& p) const
	{
		auto h1 = std::hash<T1>{}(p.first);
		auto h2 = std::hash<T2>{}(p.second);
		return h1 ^ h2;
	}
};

class PublicManager
{
public:
	static void InitOnPluginStart(IPluginContext* pContext);

	// ENTITY.INC
	#include "API/EntityAPI.h"

	// SDKTOOLS_FUNCTIONS.INC
	#include "API/SDKToolsFunctions.h"

	// SDKHOOKS.INC
	#include "API/SDKHooksAPI.h"

	// MENUS.INC
	#include "API/MenusAPI.h"

	// EVENTS.INC
	#include "API/EventsAPI.h"

	// DBI.INC
	#include "API/DbiAPI.h"

	// CSTIKE.INC
	#include "API/CStrikeAPI.h"

	// CONSOLE.INC
	#include "API/ConsoleAPI.h"

	// CLIENT.INC
	#include "API/ClientAPI.h"
private:
	static void PushArg(IPluginFunction* func, int arg) { func->PushCell(arg); }
	static void PushArg(IPluginFunction* func, float arg) { func->PushFloat(arg); }
	static void PushArg(IPluginFunction* func, const char* arg) { func->PushString(arg); }
	static void PushArg(IPluginFunction* func, float arg[3]) { func->PushArray((int*)arg, 3, 1); }
	static void PushArg(IPluginFunction* func, const float arg[3]) { func->PushArray((int*)arg, 3, 1); }
	static void PushArg(IPluginFunction* func, int arg[], unsigned int len) { func->PushArray(arg, len); }

	static void PushArgRef(IPluginFunction* func, int& arg) { func->PushCellByRef(&arg); }
	static void PushArgRef(IPluginFunction* func, float& arg) { func->PushFloatByRef(&arg); }
	static void PushArgRef(IPluginFunction* func, const char* arg) { func->PushString(arg); }

	static int ExecAndReturn(IPluginFunction* func)
	{
		cell_t res;
		func->Execute(&res);
		return res;
	}

	static int ExecFunc(IPluginFunction* func) { return ExecAndReturn(func); }

	template<typename T1>
	static int ExecFunc(IPluginFunction* func, T1 t1)
	{
		PushArg(func, t1);
		return ExecAndReturn(func);
	}

	template<typename T1, typename T2>
	static int ExecFunc(IPluginFunction* func, T1 t1, T2 t2)
	{
		PushArg(func, t1); PushArg(func, t2);
		return ExecAndReturn(func);
	}

	template<typename T1, typename T2, typename T3>
	static int ExecFunc(IPluginFunction* func, T1 t1, T2 t2, T3 t3)
	{
		PushArg(func, t1); PushArg(func, t2); PushArg(func, t3);
		return ExecAndReturn(func);
	}

	template<typename T1, typename T2, typename T3, typename T4>
	static int ExecFunc(IPluginFunction* func, T1 t1, T2 t2, T3 t3, T4 t4)
	{
		PushArg(func, t1); PushArg(func, t2); PushArg(func, t3); PushArg(func, t4);
		return ExecAndReturn(func);
	}

	template<typename T1, typename T2, typename T3, typename T4, typename T5>
	static int ExecFunc(IPluginFunction* func, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
	{
		PushArg(func, t1); PushArg(func, t2); PushArg(func, t3);
		PushArg(func, t4); PushArg(func, t5);
		return ExecAndReturn(func);
	}

	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	static int ExecFunc(IPluginFunction* func, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
	{
		PushArg(func, t1); PushArg(func, t2); PushArg(func, t3);
		PushArg(func, t4); PushArg(func, t5); PushArg(func, t6);
		return ExecAndReturn(func);
	}

	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	static int ExecFunc(IPluginFunction* func, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
	{
		PushArg(func, t1); PushArg(func, t2); PushArg(func, t3); PushArg(func, t4);
		PushArg(func, t5); PushArg(func, t6); PushArg(func, t7); PushArg(func, t8);
		return ExecAndReturn(func);
	}
private:
	friend class NativeManager;

	// SDKHOOKS.INC
	static std::unordered_map<std::pair<int, SDKHookType>, void*, pair_hash> s_SDKHooksCallbacks;

	// MENUS.INC
	static std::unordered_map<Handle, MenuHandler> s_MenuHandlers;
	static std::unordered_map<Handle, VoteHandler> s_VoteHandlers;

	// EVENTS.INC
	static std::unordered_map<std::string, EventHookCallback> s_EventHookCallbacksPre;
	static std::unordered_map<std::string, EventHookCallback> s_EventHookCallbacksPost;
	static std::unordered_map<std::string, EventHookCallback> s_EventHookCallbacksPostNoCopy;

	// DBI.INC
	static std::unordered_map<int, SQLTCallbackFunc> s_SQLTConnectCallbacks;
	static std::unordered_map<int, int> s_SQLTConnectCallbacksData;
	static std::unordered_map<int, SQLTCallbackFunc> s_SQLTQueryCallbacks;
	static std::unordered_map<int, int> s_SQLTQueryCallbacksData;
private:
	static int s_MaxClients;

	// ENTITY.INC
	static IPluginFunction* s_GetMaxEntitiesFunc;
	static IPluginFunction* s_GetEntityCountFunc;
	static IPluginFunction* s_IsValidEntityFunc;
	static IPluginFunction* s_IsValidEdictFunc;
	static IPluginFunction* s_IsEntNetworkableFunc;
	static IPluginFunction* s_CreateEdictFunc;
	static IPluginFunction* s_RemoveEdictFunc;
	static IPluginFunction* s_RemoveEntityFunc;
	static IPluginFunction* s_GetEdictFlagsFunc;
	static IPluginFunction* s_SetEdictFlagsFunc;
	static IPluginFunction* s_GetEdictClassnameFunc;
	static IPluginFunction* s_GetEntityNetClassFunc;
	static IPluginFunction* s_ChangeEdictStateFunc;
	static IPluginFunction* s_GetEntDataFunc;
	static IPluginFunction* s_SetEntDataFunc;
	static IPluginFunction* s_GetEntDataFloatFunc;
	static IPluginFunction* s_SetEntDataFloatFunc;
	static IPluginFunction* s_GetEntDataEnt2Func;
	static IPluginFunction* s_SetEntDataEnt2Func;
	static IPluginFunction* s_GetEntDataVectorFunc;
	static IPluginFunction* s_SetEntDataVectorFunc;
	static IPluginFunction* s_GetEntDataStringFunc;
	static IPluginFunction* s_SetEntDataStringFunc;
	static IPluginFunction* s_FindSendPropInfoFunc;
	static IPluginFunction* s_FindDataMapInfoFunc;
	static IPluginFunction* s_GetEntPropFunc;
	static IPluginFunction* s_SetEntPropFunc;
	static IPluginFunction* s_GetEntPropFloatFunc;
	static IPluginFunction* s_SetEntPropFloatFunc;
	static IPluginFunction* s_GetEntPropEntFunc;
	static IPluginFunction* s_SetEntPropEntFunc;
	static IPluginFunction* s_GetEntPropVectorFunc;
	static IPluginFunction* s_SetEntPropVectorFunc;
	static IPluginFunction* s_GetEntPropStringFunc;
	static IPluginFunction* s_SetEntPropStringFunc;
	static IPluginFunction* s_GetEntPropArraySizeFunc;
	static IPluginFunction* s_GetEntityAddressFunc;

	// SDKTOOLS_FUNCTIONS.INC
	static IPluginFunction* s_RemovePlayerItemFunc;
	static IPluginFunction* s_GivePlayerItemFunc;
	static IPluginFunction* s_GetPlayerWeaponSlotFunc;
	static IPluginFunction* s_IgniteEntityFunc;
	static IPluginFunction* s_ExtinguishEntityFunc;
	static IPluginFunction* s_TeleportEntityFunc;
	static IPluginFunction* s_ForcePlayerSuicideFunc;
	static IPluginFunction* s_SlapPlayerFunc;
	static IPluginFunction* s_FindEntityByClassnameFunc;
	static IPluginFunction* s_GetClientEyeAnglesFunc;
	static IPluginFunction* s_CreateEntityByNameFunc;
	static IPluginFunction* s_DispatchSpawnFunc;
	static IPluginFunction* s_DispatchKeyValueFunc;
	static IPluginFunction* s_DispatchKeyValueFloatFunc;
	static IPluginFunction* s_DispatchKeyValueVectorFunc;
	static IPluginFunction* s_GetClientAimTargetFunc;
	static IPluginFunction* s_GetTeamCountFunc;
	static IPluginFunction* s_GetTeamNameFunc;
	static IPluginFunction* s_GetTeamScoreFunc;
	static IPluginFunction* s_SetTeamScoreFunc;
	static IPluginFunction* s_GetTeamClientCountFunc;
	static IPluginFunction* s_GetTeamEntityFunc;
	static IPluginFunction* s_SetEntityModelFunc;
	static IPluginFunction* s_GetPlayerDecalFileFunc;
	static IPluginFunction* s_GetPlayerJingleFileFunc;
	static IPluginFunction* s_GetServerNetStatsFunc;
	static IPluginFunction* s_EquipPlayerWeaponFunc;
	static IPluginFunction* s_ActivateEntityFunc;
	static IPluginFunction* s_SetClientInfoFunc;
	static IPluginFunction* s_SetClientNameFunc;
	static IPluginFunction* s_GivePlayerAmmoFunc;

	// SDKHOOKS.INC
	static IPluginFunction* s_SDKHookFunc;
	static IPluginFunction* s_SDKHookExFunc;
	static IPluginFunction* s_SDKUnhookFunc;
	static IPluginFunction* s_SDKHooks_TakeDamageFunc;
	static IPluginFunction* s_SDKHooks_DropWeaponFunc;

	// MENUS.INC
	static IPluginFunction* s_CreateMenuFunc;
	static IPluginFunction* s_DisplayMenuFunc;
	static IPluginFunction* s_DisplayMenuAtItemFunc;
	static IPluginFunction* s_AddMenuItemFunc;
	static IPluginFunction* s_InsertMenuItemFunc;
	static IPluginFunction* s_RemoveMenuItemFunc;
	static IPluginFunction* s_RemoveAllMenuItemsFunc;
	static IPluginFunction* s_GetMenuItemFunc;
	static IPluginFunction* s_MenuShufflePerClientFunc;
	static IPluginFunction* s_MenuSetClientMappingFunc;
	static IPluginFunction* s_GetMenuSelectionPositionFunc;
	static IPluginFunction* s_GetMenuItemCountFunc;
	static IPluginFunction* s_SetMenuPaginationFunc;
	static IPluginFunction* s_GetMenuPaginationFunc;
	static IPluginFunction* s_GetMenuStyleFunc;
	static IPluginFunction* s_SetMenuTitleFunc;
	static IPluginFunction* s_GetMenuTitleFunc;
	static IPluginFunction* s_CreatePanelFromMenuFunc;
	static IPluginFunction* s_GetMenuExitButtonFunc;
	static IPluginFunction* s_SetMenuExitButtonFunc;
	static IPluginFunction* s_GetMenuExitBackButtonFunc;
	static IPluginFunction* s_SetMenuExitBackButtonFunc;
	static IPluginFunction* s_SetMenuNoVoteButtonFunc;
	static IPluginFunction* s_CancelMenuFunc;
	static IPluginFunction* s_GetMenuOptionFlagsFunc;
	static IPluginFunction* s_SetMenuOptionFlagsFunc;
	static IPluginFunction* s_IsVoteInProgressFunc;
	static IPluginFunction* s_CancelVoteFunc;
	static IPluginFunction* s_VoteMenuFunc;
	static IPluginFunction* s_SetVoteResultCallbackFunc;
	static IPluginFunction* s_CheckVoteDelayFunc;
	static IPluginFunction* s_IsClientInVotePoolFunc;
	static IPluginFunction* s_RedrawClientVoteMenuFunc;
	static IPluginFunction* s_GetMenuStyleHandleFunc;
	static IPluginFunction* s_CreatePanelFunc;
	static IPluginFunction* s_CreateMenuExFunc;
	static IPluginFunction* s_GetClientMenuFunc;
	static IPluginFunction* s_CancelClientMenuFunc;
	static IPluginFunction* s_GetMaxPageItemsFunc;
	static IPluginFunction* s_GetPanelStyleFunc;
	static IPluginFunction* s_SetPanelTitleFunc;
	static IPluginFunction* s_DrawPanelItemFunc;
	static IPluginFunction* s_DrawPanelTextFunc;
	static IPluginFunction* s_CanPanelDrawFlagsFunc;
	static IPluginFunction* s_SetPanelKeysFunc;
	static IPluginFunction* s_SendPanelToClientFunc;
	static IPluginFunction* s_GetPanelTextRemainingFunc;
	static IPluginFunction* s_GetPanelCurrentKeyFunc;
	static IPluginFunction* s_SetPanelCurrentKeyFunc;
	static IPluginFunction* s_RedrawMenuItemFunc;
	static IPluginFunction* s_InternalShowMenuFunc;

	// EVENTS.INC
	static IPluginFunction* s_HookEventFunc;
	static IPluginFunction* s_HookEventExFunc;
	static IPluginFunction* s_UnhookEventFunc;
	static IPluginFunction* s_CreateEventFunc;
	static IPluginFunction* s_FireEventFunc;
	static IPluginFunction* s_CancelCreatedEventFunc;
	static IPluginFunction* s_GetEventBoolFunc;
	static IPluginFunction* s_SetEventBoolFunc;
	static IPluginFunction* s_GetEventIntFunc;
	static IPluginFunction* s_SetEventIntFunc;
	static IPluginFunction* s_GetEventFloatFunc;
	static IPluginFunction* s_SetEventFloatFunc;
	static IPluginFunction* s_GetEventStringFunc;
	static IPluginFunction* s_SetEventStringFunc;
	static IPluginFunction* s_GetEventNameFunc;
	static IPluginFunction* s_SetEventBroadcastFunc;

	// DBI.INC
	static IPluginFunction* s_SQL_ConnectFunc;
	static IPluginFunction* s_SQL_ConnectCustomFunc;
	static IPluginFunction* s_SQL_CheckConfigFunc;
	static IPluginFunction* s_SQL_GetDriverFunc;
	static IPluginFunction* s_SQL_ReadDriverFunc;
	static IPluginFunction* s_SQL_GetDriverIdentFunc;
	static IPluginFunction* s_SQL_GetDriverProductFunc;
	static IPluginFunction* s_SQL_SetCharsetFunc;
	static IPluginFunction* s_SQL_GetAffectedRowsFunc;
	static IPluginFunction* s_SQL_GetInsertIdFunc;
	static IPluginFunction* s_SQL_GetErrorFunc;
	static IPluginFunction* s_SQL_EscapeStringFunc;
	static IPluginFunction* s_SQL_FormatQueryFunc;
	static IPluginFunction* s_SQL_FastQueryFunc;
	static IPluginFunction* s_SQL_QueryFunc;
	static IPluginFunction* s_SQL_PrepareQueryFunc;
	static IPluginFunction* s_SQL_FetchMoreResultsFunc;
	static IPluginFunction* s_SQL_HasResultSetFunc;
	static IPluginFunction* s_SQL_GetRowCountFunc;
	static IPluginFunction* s_SQL_GetFieldCountFunc;
	static IPluginFunction* s_SQL_FieldNumToNameFunc;
	static IPluginFunction* s_SQL_FieldNameToNumFunc;
	static IPluginFunction* s_SQL_FetchRowFunc;
	static IPluginFunction* s_SQL_MoreRowsFunc;
	static IPluginFunction* s_SQL_RewindFunc;
	static IPluginFunction* s_SQL_FetchStringFunc;
	static IPluginFunction* s_SQL_FetchFloatFunc;
	static IPluginFunction* s_SQL_FetchIntFunc;
	static IPluginFunction* s_SQL_IsFieldNullFunc;
	static IPluginFunction* s_SQL_FetchSizeFunc;
	static IPluginFunction* s_SQL_BindParamIntFunc;
	static IPluginFunction* s_SQL_BindParamFloatFunc;
	static IPluginFunction* s_SQL_BindParamStringFunc;
	static IPluginFunction* s_SQL_ExecuteFunc;
	static IPluginFunction* s_SQL_LockDatabaseFunc;
	static IPluginFunction* s_SQL_UnlockDatabaseFunc;
	static IPluginFunction* s_SQL_IsSameConnectionFunc;
	static IPluginFunction* s_SQL_TConnectFunc;
	static IPluginFunction* s_SQL_TQueryFunc;
	static IPluginFunction* s_SQL_CreateTransactionFunc;
	static IPluginFunction* s_SQL_AddQueryFunc;
	static IPluginFunction* s_SQL_ExecuteTransactionFunc;

	// CSTRIKE.INC
	static IPluginFunction* s_CS_RespawnPlayerFunc;
	static IPluginFunction* s_CS_SwitchTeamFunc;
	static IPluginFunction* s_CS_DropWeaponFunc;
	static IPluginFunction* s_CS_TerminateRoundFunc;
	static IPluginFunction* s_CS_GetTranslatedWeaponAliasFunc;
	static IPluginFunction* s_CS_GetWeaponPriceFunc;
	static IPluginFunction* s_CS_GetClientClanTagFunc;
	static IPluginFunction* s_CS_SetClientClanTagFunc;
	static IPluginFunction* s_CS_GetTeamScoreFunc;
	static IPluginFunction* s_CS_SetTeamScoreFunc;
	static IPluginFunction* s_CS_GetMVPCountFunc;
	static IPluginFunction* s_CS_SetMVPCountFunc;
	static IPluginFunction* s_CS_GetClientContributionScoreFunc;
	static IPluginFunction* s_CS_SetClientContributionScoreFunc;
	static IPluginFunction* s_CS_GetClientAssistsFunc;
	static IPluginFunction* s_CS_SetClientAssistsFunc;
	static IPluginFunction* s_CS_AliasToWeaponIDFunc;
	static IPluginFunction* s_CS_WeaponIDToAliasFunc;
	static IPluginFunction* s_CS_IsValidWeaponIDFunc;
	static IPluginFunction* s_CS_UpdateClientModelFunc;
	static IPluginFunction* s_CS_ItemDefIndexToIDFunc;
	static IPluginFunction* s_CS_WeaponIDToItemDefIndexFunc;

	// CONSOLE.INC
	static IPluginFunction* s_ServerCommandFunc;
	static IPluginFunction* s_ServerCommandExFunc;
	static IPluginFunction* s_InsertServerCommandFunc;
	static IPluginFunction* s_ServerExecuteFunc;
	static IPluginFunction* s_ClientCommandFunc;
	static IPluginFunction* s_FakeClientCommandFunc;
	static IPluginFunction* s_FakeClientCommandExFunc;
	static IPluginFunction* s_FakeClientCommandKeyValuesFunc;
	static IPluginFunction* s_PrintToServerFunc;
	static IPluginFunction* s_PrintToConsoleFunc;
	static IPluginFunction* s_ReplyToCommandFunc;
	static IPluginFunction* s_GetCmdReplySourceFunc;
	static IPluginFunction* s_SetCmdReplySourceFunc;
	static IPluginFunction* s_IsChatTriggerFunc;
	static IPluginFunction* s_ShowActivity2Func;
	static IPluginFunction* s_ShowActivityFunc;
	static IPluginFunction* s_ShowActivityExFunc;
	static IPluginFunction* s_FormatActivitySourceFunc;
	static IPluginFunction* s_RegServerCmdFunc;
	static IPluginFunction* s_RegConsoleCmdFunc;
	static IPluginFunction* s_RegAdminCmdFunc;
	static IPluginFunction* s_GetCmdArgsFunc;
	static IPluginFunction* s_GetCmdArgFunc;
	static IPluginFunction* s_GetCmdArgStringFunc;
	static IPluginFunction* s_GetCommandIteratorFunc;
	static IPluginFunction* s_ReadCommandIteratorFunc;
	static IPluginFunction* s_CheckCommandAccessFunc;
	static IPluginFunction* s_CheckAccessFunc;
	static IPluginFunction* s_GetCommandFlagsFunc;
	static IPluginFunction* s_SetCommandFlagsFunc;
	static IPluginFunction* s_FindFirstConCommandFunc;
	static IPluginFunction* s_FindNextConCommandFunc;
	static IPluginFunction* s_AddServerTagFunc;
	static IPluginFunction* s_RemoveServerTagFunc;
	static IPluginFunction* s_AddCommandListenerFunc;
	static IPluginFunction* s_RemoveCommandListenerFunc;

	// CLIENTS.INC
	static IPluginFunction* s_GetMaxHumanPlayersFunc;
	static IPluginFunction* s_GetClientCountFunc;
	static IPluginFunction* s_GetClientNameFunc;
	static IPluginFunction* s_GetClientIPFunc;
	static IPluginFunction* s_GetClientAuthIdFunc;
	static IPluginFunction* s_GetSteamAccountIDFunc;
	static IPluginFunction* s_GetClientUserIdFunc;
	static IPluginFunction* s_IsClientConnectedFunc;
	static IPluginFunction* s_IsClientInGameFunc;
	static IPluginFunction* s_IsClientInKickQueueFunc;
	static IPluginFunction* s_IsClientAuthorizedFunc;
	static IPluginFunction* s_IsFakeClientFunc;
	static IPluginFunction* s_IsClientSourceTVFunc;
	static IPluginFunction* s_IsClientReplayFunc;
	static IPluginFunction* s_IsClientObserverFunc;
	static IPluginFunction* s_IsPlayerAliveFunc;
	static IPluginFunction* s_GetClientInfoFunc;
	static IPluginFunction* s_GetClientTeamFunc;
	static IPluginFunction* s_SetUserAdminFunc;
	static IPluginFunction* s_GetUserAdminFunc;
	static IPluginFunction* s_AddUserFlagsFunc;
	static IPluginFunction* s_RemoveUserFlagsFunc;
	static IPluginFunction* s_SetUserFlagBitsFunc;
	static IPluginFunction* s_GetUserFlagBitsFunc;
	static IPluginFunction* s_CanUserTargetFunc;
	static IPluginFunction* s_RunAdminCacheChecksFunc;
	static IPluginFunction* s_NotifyPostAdminCheckFunc;
	static IPluginFunction* s_CreateFakeClientFunc;
	static IPluginFunction* s_SetFakeClientConVarFunc;
	static IPluginFunction* s_GetClientHealthFunc;
	static IPluginFunction* s_GetClientModelFunc;
	static IPluginFunction* s_GetClientWeaponFunc;
	static IPluginFunction* s_GetClientMaxsFunc;
	static IPluginFunction* s_GetClientMinsFunc;
	static IPluginFunction* s_GetClientAbsAnglesFunc;
	static IPluginFunction* s_GetClientAbsOriginFunc;
	static IPluginFunction* s_GetClientArmorFunc;
	static IPluginFunction* s_GetClientDeathsFunc;
	static IPluginFunction* s_GetClientFragsFunc;
	static IPluginFunction* s_GetClientDataRateFunc;
	static IPluginFunction* s_IsClientTimingOutFunc;
	static IPluginFunction* s_GetClientTimeFunc;
	static IPluginFunction* s_GetClientLatencyFunc;
	static IPluginFunction* s_GetClientAvgLatencyFunc;
	static IPluginFunction* s_GetClientAvgLossFunc;
	static IPluginFunction* s_GetClientAvgChokeFunc;
	static IPluginFunction* s_GetClientAvgDataFunc;
	static IPluginFunction* s_GetClientAvgPacketsFunc;
	static IPluginFunction* s_GetClientOfUserIdFunc;
	static IPluginFunction* s_KickClientFunc;
	static IPluginFunction* s_KickClientExFunc;
	static IPluginFunction* s_ChangeClientTeamFunc;
	static IPluginFunction* s_GetClientSerialFunc;
	static IPluginFunction* s_GetClientFromSerialFunc;
};
