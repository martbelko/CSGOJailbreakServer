#pragma once

#include "smsdk_ext.h"

#include "Defines.h"

#include <string>
#include <sstream>
#include <unordered_map>
#include <functional>
#include <random>

#ifdef CreateDialog
	#undef CreateDialog // Windows function
#endif
#ifdef CreateEvent
	#undef CreateEvent
#endif

/* CONSOLE.INC */

using ConCmdFunc = Action(*)(int client, std::string& command, int argc);
using SrvCmdFunc = Action(*)(std::string& command, int argc);
using CommandListenerFunc = Action(*)(int client, std::string& command, int argc);

/* SDKTOOLS_ENTOUTPUT.INC */

/**
 * @brief Called when an entity output is fired.
 *
 * @param output        Name of the output that fired.
 * @param caller        Entity index of the caller.
 * @param activator     Entity index of the activator.
 * @param delay         Delay in seconds? before the event gets fired.
 * @return              Anything other than Plugin_Continue will supress this event,
 *                      returning Plugin_Continue will allow it to propagate the results
 *                      of this output to any entity inputs.
 */
using EntityOutputFunc = Action(*)(const char* output, int caller, int activator, float delay);

/* SDKHOOKS.INC */

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

/* TIMERS.INC */

using TimerCallbackFunc = Action(*)(Handle timer, void* data);

/* SDKTOOLS_TEMPENTS.INC */

/**
 * @brief Called when a temp entity is going to be sent.
 *
 * @param teName        TE name.
 * @param players       Array containing target player indexes.
 * @param numClients    Number of players in the array.
 * @param delay         Delay in seconds to send the TE.
 * @return              Plugin_Continue to allow the transmission of the TE, Plugin_Stop to block it.
 */
using TEHookFunc = Action(*)(const char* teName, const int players[], int numClients, float delay);

/* LOGGING.INC */

/**
 * @brief Called when a game log message is received.
 *
 * Any Log*() functions called within this callback will not recursively
 * pass through.  That is, they will log directly, bypassing this callback.
 *
 * Note that this does not capture log messages from the engine.  It only
 * captures log messages being sent from the game/mod itself.
 *
 * @param message       Message contents.
 * @return              Plugin_Handled or Plugin_Stop will prevent the message
 *                      from being written to the log file.
 */
using GameLogHookFunc = Action(*)(const char* message);

/* SDKTOOLS_TRACE.INC */

/**
 * Called on entity filtering.
 *
 * @param entity        Entity index.
 * @param contentsMask  Contents Mask.
 * @param data          Data value
 * @return              True to allow the current entity to be hit, otherwise false.
 */
using TraceEntityFilterFunc = bool(*)(int entity, int contentsMask, void* data);

/**
 * Called for each entity enumerated with EnumerateEntities*.
 *
 * @param entity        Entity index.
 * @param data          Data value
 * @return              True to continue enumerating, otherwise false. */
using TraceEntityEnumeratorFunc = bool(*)(int entity, void* data);

/* COMMANDFILTERS.INC */

/**
 * Adds clients to a multi-target filter.
 *
 * @param pattern       Pattern name.
 * @param clients       Array to fill with unique, valid client indexes.
 * @return              True if pattern was recognized, false otherwise.
 */
using MultiTargetFilterFunc = bool(*)(const char* pattern, Handle clients);

/* SDKTOOLS_SOUND.INC */

/**
 * Called when an ambient sound is about to be emitted to one or more clients.
 *
 * NOTICE: all parameters can be overwritten to modify the default behavior.
 *
 * @param sample        Sound file name relative to the "sound" folder.
 * @param entity        Entity index associated to the sound.
 * @param volume        Volume (from 0.0 to 1.0).
 * @param level         Sound level (from 0 to 255).
 * @param pitch         Pitch (from 0 to 255).
 * @param pos           Origin of sound.
 * @param flags         Sound flags.
 * @param delay         Play delay.
 * @return              Plugin_Continue to allow the sound to be played, Plugin_Stop to block it,
 *                      Plugin_Changed when any parameter has been modified.
 */
using AmbientSHookFunc = Action(*)(char sample[PLATFORM_MAX_PATH], int& entity, float& volume,
	int& level, int& pitch, float pos[3], int& flags, float& delay);

// Called when a sound is going to be emitted to one or more clients.
// NOTICE: all params can be overwritten to modify the default behavior.
//
// @param clients       Array of client indexes.
// @param numClients    Number of clients in the array (modify this value if you add/remove elements from the client array).
// @param sample        Sound file name relative to the "sound" folder.
// @param entity        Entity emitting the sound.
// @param channel       Channel emitting the sound.
// @param volume        Sound volume.
// @param level         Sound level.
// @param pitch         Sound pitch.
// @param flags         Sound flags.
// @param soundEntry    Game sound entry name. (Used in engines newer than Portal 2)
// @param seed          Sound seed. (Used in engines newer than Portal 2)
// @return              Plugin_Continue to allow the sound to be played, Plugin_Stop to block it,
//                      Plugin_Changed when any parameter has been modified.
using NormalSHookFunc = Action(*)(int clients[MAXPLAYERS], int& numClients, char sample[PLATFORM_MAX_PATH],
	int& entity, int& channel, float& volume, int& level, int& pitch, int& flags,
	char soundEntry[PLATFORM_MAX_PATH], int& seed);

/* CONSOLE.INC */

/**
* Called when a console variable's value is changed.
*
* @param convar        Handle to the convar that was changed.
* @param oldValue      String containing the value of the convar before it was changed.
* @param newValue      String containing the new value of the convar.
*/
using ConVarChangedFunc = void(*)(ConVarHandle convar, const char* oldValue, const char* newValue);

/**
* @brief Called when a query to retrieve a client's console variable has finished.

* @param cookie        Unique identifier of query.
* @param client        Player index.
* @param result        Result of query that tells one whether or not query was successful.
                       See ConVarQueryResult enum for more details.
* @param cvarName      Name of client convar that was queried.
* @param cvarValue     Value of client convar that was queried if successful. This will be "" if it was not.
* @param value         Value that was passed when query was started.
*/
using ConVarQueryFinishedFunc = void(*)(QueryCookie cookie, int client, ConVarQueryResult result, const char* cvarName, const char* cvarValue, void* value);

/* USERMESSAGES.INC */

/**
 * Called when a protobuf based usermessage is hooked
 *
 * @param msgID         Message index.
 * @param msg           Handle to the input (bit buffer / protobuf).
 * @param players       Array containing player indexes.
 * @param playersNum    Number of players in the array.
 * @param reliable      True if message is reliable, false otherwise.
 * @param init          True if message is an initmsg, false otherwise.
 * @return              Ignored for normal hooks.  For intercept hooks, Plugin_Handled
 *                      blocks the message from being sent, and Plugin_Continue
 *                      resumes normal functionality.
 */
using MsgHookFunc = Action(*)(UserMsg msgID, ProtobufHandle msg, const int players[], int playersNum, bool reliable, bool init);

/**
 * Called when a message hook has completed.
 *
 * @param msgID         Message index.
 * @param sent          True if message was sent, false if blocked.
 */
using MsgPostHookFunc = void(*)(UserMsg msgID, bool sent);

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

	// OWN
	static bool SDKCallSmoke3(Handle call, Address addr, float from[3], float to[3])
	{
		PushArg(s_SDKCallSmoke3Func, call);
		PushArg(s_SDKCallSmoke3Func, addr);
		PushArg(s_SDKCallSmoke3Func, from, 3);
		PushArg(s_SDKCallSmoke3Func, to, 3);
		return ExecFunc(s_SDKCallSmoke3Func);
	}

	static bool SDKCallSmoke4(Handle call, Address addr, float from[3], float to[3], float arg)
	{
		PushArg(s_SDKCallSmoke4Func, call);
		PushArg(s_SDKCallSmoke4Func, addr);
		PushArg(s_SDKCallSmoke4Func, from, 3);
		PushArg(s_SDKCallSmoke4Func, to, 3);
		PushArg(s_SDKCallSmoke4Func, arg);
		return ExecFunc(s_SDKCallSmoke4Func);
	}

	// VECTOR.INC
	#include "API/VectorAPI.h"

	// USERMESSAGES.INC
	#include "API/UserMessagesAPI.h"

	// PROTOBUF.INC
	#include "API/ProtobufAPI.h"

	// CONVARS.INC
	#include "API/ConVarsAPI.h"

	// SOURCEMOD.INC
	#include "API/SourcemodAPI.h"

	// SDKTOOLS.INC
	#include "API/SDKToolsAPI.h"

	// SDKTOOLS_SOUND.INC
	#include "API/SDKToolsSoundAPI.h"

	// HELPERS.INC
	#include "API/HelpersAPI.h"

	// COMMANDFILTERS.INC
	#include "API/CommandFiltersAPI.h"

	// ADT_ARRAY.INC
	#include "API/ADTArrayAPI.h"

	// LANG.INC
	#include "API/LangAPI.h"

	// SDKTOOLS_VOICE.INC
	#include "API/SDKToolsVoiceAPI.h"

	// STRING.INC
	#include "API/StringAPI.h"

	// GEOIP.INC
	#include "API/GeoIPAPI.h"

	// SDKTOOLS_CLIENT.INC
	#include "API/SDKToolsClientAPI.h"

	// SDKTOOLS_ENGINE.INC
	#include "API/SDKToolsEngineAPI.h"

	// SDKTOOLS_TRACE.INC
	#include "API/SDKToolsTraceAPI.h"

	// BITBUFFER.INC
	#include "API/BitBufferAPI.h"

	// LOGGING.INC
	#include "API/LoggingAPI.h"

	// SDKTOOLS_STOCKS.INC
	#include "API/SDKToolsStocksAPI.h"

	// SDKTOOLS_TEMPENTS_STOCKS.INC
	#include "API/SDKToolsTempentsStocksAPI.h"

	// SDKTOOLS_TEMPENTS.INC
	#include "API/SDKToolsTempentsAPI.h"

	// SDKTOOLS_GAMERULES.INC
	#include "API/SDKToolsGameRulesAPI.h"

	// SDKTOOLS_ENTINPUT.INC
	// SDKTOOLS_ENTOUTPUT.INC
	#include "API/SDKToolsEntInOutAPI.h"

	// HANDLES.INC
	#include "API/HandlesAPI.h"

	// ENTITY_PROP_STOCKS.INC
	#include "API/EntityPropStocksAPI.h"

	// HALFLIFE.INC
	#include "API/HalfLifeAPI.h"

	// TIMERS.INC
	#include "API/TimersAPI.h"

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
	static int GetMaxClients() { return s_MaxClients; }
	#include "API/ClientAPI.h"
private:
	static void PushArg(IPluginFunction* func, int arg) { func->PushCell(arg); }
	static void PushArg(IPluginFunction* func, float arg) { func->PushFloat(arg); }
	static void PushArg(IPluginFunction* func, const char* arg) { func->PushString(arg); }
	static void PushArg(IPluginFunction* func, char* arg, unsigned int len) { func->PushStringEx(arg, len, 0, 1); }
	static void PushArg(IPluginFunction* func, float arg[3]) { func->PushArray((int*)arg, 3, 1); } // TODO: Remove
	static void PushArg(IPluginFunction* func, const float arg[3]) { func->PushArray((int*)arg, 3, 0); } // TODO: Remove
	static void PushArg(IPluginFunction* func, const float* arg, unsigned int len) { func->PushArray(const_cast<int*>(reinterpret_cast<const int*>(arg)), len, 0); }
	static void PushArg(IPluginFunction* func, float* arg, unsigned int len) { func->PushArray(reinterpret_cast<int*>(arg), len, 1); }
	static void PushArg(IPluginFunction* func, int* arg, unsigned int len) { func->PushArray(arg, len, 1); }
	static void PushArg(IPluginFunction* func, const int* arg, unsigned int len) { func->PushArray(const_cast<int*>(arg), len, 0); }

	static void PushArgRef(IPluginFunction* func, int& arg) { func->PushCellByRef(&arg); }
	static void PushArgRef(IPluginFunction* func, float& arg) { func->PushFloatByRef(&arg); }
	static void PushArgRef(IPluginFunction* func, const char* arg) { func->PushString(arg); }

	static int ExecAndReturn(IPluginFunction* func)
	{
		cell_t res;
		func->Execute(&res);
		return res;
	}

	static int ExecFunc(IPluginFunction* func)
	{
		return ExecAndReturn(func);
	}

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

	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8, typename T9, typename T10, typename T11>
	static int ExecFunc(IPluginFunction* func, T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8, T9 t9, T10 t10, T11 t11)
	{
		PushArg(func, t1); PushArg(func, t2); PushArg(func, t3); PushArg(func, t4);
		PushArg(func, t5); PushArg(func, t6); PushArg(func, t7); PushArg(func, t8);
		PushArg(func, t9); PushArg(func, t10); PushArg(func, t11);
		return ExecAndReturn(func);
	}
private:
	friend class NativeManager;

	// OWN
	static IPluginFunction* s_SDKCallSmoke3Func;
	static IPluginFunction* s_SDKCallSmoke4Func;

	static AmbientSHookFunc s_AmbientSHookCallback;
	static NormalSHookFunc s_NormalSHookCallback;

	// USERMESSAGES.INC
	static std::unordered_map<UserMsg, MsgHookFunc> s_MsgHookCallbacks;
	static std::unordered_map<UserMsg, MsgPostHookFunc> s_MsgPostHookCallbacks;

	// CONVARS.INC
	static std::unordered_map<Handle, ConVarChangedFunc> s_ConVarChangedCallbacks;
	static std::unordered_map<std::pair<int, std::string>, ConVarQueryFinishedFunc, pair_hash> s_ConVarFinishedCallbacks;

	// COMMANDFILTERS.INC
	static std::unordered_map<std::string, MultiTargetFilterFunc> s_MultiTargetFilterCallbacks;

	// SDKTOOLS_TRACE.INC
	static int s_TraceEntityFilterIndex;
	static std::unordered_map<int, TraceEntityFilterFunc> s_TraceEntityFilterCallbacks;
	static std::unordered_map<int, void*> s_TraceEntityFilterData;

	static int s_TraceEntityEnumeratorIndex;
	static std::unordered_map<int, TraceEntityEnumeratorFunc> s_TraceEntityEnumeratorCallbacks;
	static std::unordered_map<int, void*> s_TraceEntityEnumeratorData;

	// LOGGING.INC
	static GameLogHookFunc s_GameLogHookCallback;

	// SDKTOOLS_TEMPENTS.INC
	static std::unordered_map<std::string, TEHookFunc> s_TEHooksCallbacks;

	// SDKTOOLS_ENTOUTPUT.INC
	static std::unordered_map<std::pair<std::string, std::string>, EntityOutputFunc, pair_hash> s_EntityOutputCallbacks;
	static std::unordered_map<std::pair<int, std::string>, EntityOutputFunc, pair_hash> s_SingleEntityOutputCallbacks;

	// TIMERS.INC
	static std::unordered_map<Handle, TimerCallbackFunc> s_TimerCallbacks;

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

	// CONSOLE.INC
	static std::unordered_map<std::string, ConCmdFunc> s_ConCmdCallbacks;
	static std::unordered_map<std::string, SrvCmdFunc> s_SrvCmdCallbacks;
	static std::unordered_map<std::string, CommandListenerFunc> s_CommandListenerCallbacks;
private:
	static int s_MaxClients;

	// USERMESSAGES.INC
	static IPluginFunction* s_GetUserMessageTypeFunc;
	static IPluginFunction* s_GetUserMessageIdFunc;
	static IPluginFunction* s_GetUserMessageNameFunc;
	static IPluginFunction* s_StartMessageFunc;
	static IPluginFunction* s_StartMessageExFunc;
	static IPluginFunction* s_EndMessageFunc;
	static IPluginFunction* s_HookUserMessageFunc;
	static IPluginFunction* s_UnhookUserMessageFunc;

	// PROTOBUF.INC
	static IPluginFunction* s_PbReadIntFunc;
	static IPluginFunction* s_PbReadFloatFunc;
	static IPluginFunction* s_PbReadBoolFunc;
	static IPluginFunction* s_PbReadStringFunc;
	static IPluginFunction* s_PbReadColorFunc;
	static IPluginFunction* s_PbReadAngleFunc;
	static IPluginFunction* s_PbReadVectorFunc;
	static IPluginFunction* s_PbReadVector2DFunc;
	static IPluginFunction* s_PbGetRepeatedFieldCountFunc;
	static IPluginFunction* s_PbSetIntFunc;
	static IPluginFunction* s_PbSetFloatFunc;
	static IPluginFunction* s_PbSetBoolFunc;
	static IPluginFunction* s_PbSetStringFunc;
	static IPluginFunction* s_PbSetColorFunc;
	static IPluginFunction* s_PbSetAngleFunc;
	static IPluginFunction* s_PbSetVectorFunc;
	static IPluginFunction* s_PbSetVector2DFunc;
	static IPluginFunction* s_PbAddIntFunc;
	static IPluginFunction* s_PbAddFloatFunc;
	static IPluginFunction* s_PbAddBoolFunc;
	static IPluginFunction* s_PbAddStringFunc;
	static IPluginFunction* s_PbAddColorFunc;
	static IPluginFunction* s_PbAddAngleFunc;
	static IPluginFunction* s_PbAddVectorFunc;
	static IPluginFunction* s_PbAddVector2DFunc;
	static IPluginFunction* s_PbRemoveRepeatedFieldValueFunc;
	static IPluginFunction* s_PbReadMessageFunc;
	static IPluginFunction* s_PbReadRepeatedMessageFunc;
	static IPluginFunction* s_PbAddMessageFunc;

	// CONVARS.INC
	static IPluginFunction* s_CreateConVarFunc;
	static IPluginFunction* s_FindConVarFunc;
	static IPluginFunction* s_HookConVarChangeFunc;
	static IPluginFunction* s_UnhookConVarChangeFunc;
	static IPluginFunction* s_GetConVarBoolFunc;
	static IPluginFunction* s_SetConVarBoolFunc;
	static IPluginFunction* s_GetConVarIntFunc;
	static IPluginFunction* s_SetConVarIntFunc;
	static IPluginFunction* s_GetConVarFloatFunc;
	static IPluginFunction* s_SetConVarFloatFunc;
	static IPluginFunction* s_GetConVarStringFunc;
	static IPluginFunction* s_SetConVarStringFunc;
	static IPluginFunction* s_ResetConVarFunc;
	static IPluginFunction* s_GetConVarDefaultFunc;
	static IPluginFunction* s_GetConVarFlagsFunc;
	static IPluginFunction* s_SetConVarFlagsFunc;
	static IPluginFunction* s_GetConVarBoundsFunc;
	static IPluginFunction* s_SetConVarBoundsFunc;
	static IPluginFunction* s_GetConVarNameFunc;
	static IPluginFunction* s_SendConVarValueFunc;
	static IPluginFunction* s_QueryClientConVarFunc;

	// SOURCEMOD.INC
	static IPluginFunction* s_GetMyHandleFunc;
	static IPluginFunction* s_GetPluginIteratorFunc;
	static IPluginFunction* s_MorePluginsFunc;
	static IPluginFunction* s_ReadPluginFunc;
	static IPluginFunction* s_GetPluginStatusFunc;
	static IPluginFunction* s_GetPluginFilenameFunc;
	static IPluginFunction* s_IsPluginDebuggingFunc;
	static IPluginFunction* s_GetPluginInfoFunc;
	static IPluginFunction* s_FindPluginByNumberFunc;
	static IPluginFunction* s_SetFailStateFunc;
	static IPluginFunction* s_ThrowErrorFunc;
	static IPluginFunction* s_LogStackTraceFunc;
	static IPluginFunction* s_GetTimeFunc;
	static IPluginFunction* s_FormatTimeFunc;
	static IPluginFunction* s_LoadGameConfigFileFunc;
	static IPluginFunction* s_GameConfGetOffsetFunc;
	static IPluginFunction* s_GameConfGetKeyValueFunc;
	static IPluginFunction* s_GameConfGetAddressFunc;
	static IPluginFunction* s_GetSysTickCountFunc;
	static IPluginFunction* s_AutoExecConfigFunc;
	static IPluginFunction* s_RegPluginLibraryFunc;
	static IPluginFunction* s_LibraryExistsFunc;
	static IPluginFunction* s_GetExtensionFileStatusFunc;
	static IPluginFunction* s_ReadMapListFunc;
	static IPluginFunction* s_SetMapListCompatBindFunc;
	static IPluginFunction* s_GetFeatureStatusFunc;
	static IPluginFunction* s_RequireFeatureFunc;
	static IPluginFunction* s_LoadFromAddressFunc;
	static IPluginFunction* s_StoreToAddressFunc;

	// SDKTOOLS.INC
	static IPluginFunction* s_StartPrepSDKCallFunc;
	static IPluginFunction* s_PrepSDKCall_SetVirtualFunc;
	static IPluginFunction* s_PrepSDKCall_SetSignatureFunc;
	static IPluginFunction* s_PrepSDKCall_SetAddressFunc;
	static IPluginFunction* s_PrepSDKCall_SetFromConfFunc;
	static IPluginFunction* s_PrepSDKCall_SetReturnInfoFunc;
	static IPluginFunction* s_PrepSDKCall_AddParameterFunc;
	static IPluginFunction* s_EndPrepSDKCallFunc;
	static IPluginFunction* s_SDKCall0Func;
	static IPluginFunction* s_SDKCall1Func;
	static IPluginFunction* s_SDKCall2Func;
	static IPluginFunction* s_SDKCall3Func;
	static IPluginFunction* s_SDKCall4Func;
	static IPluginFunction* s_SDKCall5Func;
	static IPluginFunction* s_SDKCall6Func;
	static IPluginFunction* s_SDKCall7Func;
	static IPluginFunction* s_SDKCall8Func;
	static IPluginFunction* s_SDKCall9Func;
	static IPluginFunction* s_SDKCall10Func;
	static IPluginFunction* s_GetPlayerResourceEntityFunc;

	// SDKTOOLS_SOUND.INC
	static IPluginFunction* s_PrefetchSoundFunc;
	static IPluginFunction* s_EmitAmbientSoundFunc;
	static IPluginFunction* s_FadeClientVolumeFunc;
	static IPluginFunction* s_StopSoundFunc;
	static IPluginFunction* s_EmitSoundFunc;
	static IPluginFunction* s_EmitSoundEntryFunc;
	static IPluginFunction* s_EmitSentenceFunc;
	static IPluginFunction* s_GetDistGainFromSoundLevelFunc;
	static IPluginFunction* s_AddAmbientSoundHookFunc;
	static IPluginFunction* s_AddNormalSoundHookFunc;
	static IPluginFunction* s_RemoveAmbientSoundHookFunc;
	static IPluginFunction* s_RemoveNormalSoundHookFunc;
	static IPluginFunction* s_GetGameSoundParamsFunc;
	static IPluginFunction* s_PrecacheScriptSoundFunc;

	// COMMANDFILTERS.INC
	static IPluginFunction* s_ProcessTargetStringFunc;
	static IPluginFunction* s_AddMultiTargetFilterFunc;
	static IPluginFunction* s_RemoveMultiTargetFilterFunc;

	// ADT_ARRAY.INC
	static IPluginFunction* s_CreateArrayFunc;
	static IPluginFunction* s_ClearArrayFunc;
	static IPluginFunction* s_CloneArrayFunc;
	static IPluginFunction* s_ResizeArrayFunc;
	static IPluginFunction* s_GetArraySizeFunc;
	static IPluginFunction* s_PushArrayCellFunc;
	static IPluginFunction* s_PushArrayStringFunc;
	static IPluginFunction* s_PushArrayArrayFunc;
	static IPluginFunction* s_GetArrayCellFunc;
	static IPluginFunction* s_GetArrayStringFunc;
	static IPluginFunction* s_GetArrayArrayFunc;
	static IPluginFunction* s_SetArrayCellFunc;
	static IPluginFunction* s_SetArrayStringFunc;
	static IPluginFunction* s_SetArrayArrayFunc;
	static IPluginFunction* s_ShiftArrayUpFunc;
	static IPluginFunction* s_RemoveFromArrayFunc;
	static IPluginFunction* s_SwapArrayItemsFunc;
	static IPluginFunction* s_FindStringInArrayFunc;
	static IPluginFunction* s_FindValueInArrayFunc;
	static IPluginFunction* s_GetArrayBlockSizeFunc;

	// LANG.INC
	static IPluginFunction* s_LoadTranslationsFunc;
	static IPluginFunction* s_SetGlobalTransTargetFunc;
	static IPluginFunction* s_GetClientLanguageFunc;
	static IPluginFunction* s_GetServerLanguageFunc;
	static IPluginFunction* s_GetLanguageCountFunc;
	static IPluginFunction* s_GetLanguageInfoFunc;
	static IPluginFunction* s_SetClientLanguageFunc;
	static IPluginFunction* s_GetLanguageByCodeFunc;
	static IPluginFunction* s_GetLanguageByNameFunc;
	static IPluginFunction* s_TranslationPhraseExistsFunc;
	static IPluginFunction* s_IsTranslatedForLanguageFunc;

	// SDKTOOLS_VOICE.INC
	static IPluginFunction* s_SetClientListeningFlagsFunc;
	static IPluginFunction* s_GetClientListeningFlagsFunc;
	static IPluginFunction* s_SetListenOverrideFunc;
	static IPluginFunction* s_GetListenOverrideFunc;
	static IPluginFunction* s_IsClientMutedFunc;

	// STRING.INC
	static IPluginFunction* s_FormatFunc;

	// GEOIP.INC
	static IPluginFunction* s_GeoipCode2Func;
	static IPluginFunction* s_GeoipCode3Func;
	static IPluginFunction* s_GeoipCountryFunc;

	// SDKTOOLS_CLIENT.INC
	static IPluginFunction* s_InactivateClientFunc;
	static IPluginFunction* s_ReconnectClientFunc;

	// SDKTOOLS_ENGINE.INC
	static IPluginFunction* s_SetClientViewEntityFunc;
	static IPluginFunction* s_SetLightStyleFunc;
	static IPluginFunction* s_GetClientEyePositionFunc;

	// SDKTOOLS_TRACE.INC
	static IPluginFunction* s_TR_GetPointContentsFunc;
	static IPluginFunction* s_TR_GetPointContentsEntFunc;
	static IPluginFunction* s_TR_TraceRayFunc;
	static IPluginFunction* s_TR_TraceHullFunc;
	static IPluginFunction* s_TR_EnumerateEntitiesFunc;
	static IPluginFunction* s_TR_EnumerateEntitiesHullFunc;
	static IPluginFunction* s_TR_EnumerateEntitiesSphereFunc;
	static IPluginFunction* s_TR_EnumerateEntitiesBoxFunc;
	static IPluginFunction* s_TR_EnumerateEntitiesPointFunc;
	static IPluginFunction* s_TR_TraceRayFilterFunc;
	static IPluginFunction* s_TR_TraceHullFilterFunc;
	static IPluginFunction* s_TR_ClipRayToEntityFunc;
	static IPluginFunction* s_TR_ClipRayHullToEntityFunc;
	static IPluginFunction* s_TR_ClipCurrentRayToEntityFunc;
	static IPluginFunction* s_TR_TraceRayExFunc;
	static IPluginFunction* s_TR_TraceHullExFunc;
	static IPluginFunction* s_TR_TraceRayFilterExFunc;
	static IPluginFunction* s_TR_TraceHullFilterExFunc;
	static IPluginFunction* s_TR_ClipRayToEntityExFunc;
	static IPluginFunction* s_TR_ClipRayHullToEntityExFunc;
	static IPluginFunction* s_TR_ClipCurrentRayToEntityExFunc;
	static IPluginFunction* s_TR_GetFractionFunc;
	static IPluginFunction* s_TR_GetFractionLeftSolidFunc;
	static IPluginFunction* s_TR_GetStartPositionFunc;
	static IPluginFunction* s_TR_GetEndPositionFunc;
	static IPluginFunction* s_TR_GetEntityIndexFunc;
	static IPluginFunction* s_TR_GetDisplacementFlagsFunc;
	static IPluginFunction* s_TR_GetSurfaceNameFunc;
	static IPluginFunction* s_TR_GetSurfacePropsFunc;
	static IPluginFunction* s_TR_GetSurfaceFlagsFunc;
	static IPluginFunction* s_TR_GetPhysicsBoneFunc;
	static IPluginFunction* s_TR_AllSolidFunc;
	static IPluginFunction* s_TR_StartSolidFunc;
	static IPluginFunction* s_TR_DidHitFunc;
	static IPluginFunction* s_TR_GetHitGroupFunc;
	static IPluginFunction* s_TR_GetHitBoxIndexFunc;
	static IPluginFunction* s_TR_GetPlaneNormalFunc;
	static IPluginFunction* s_TR_PointOutsideWorldFunc;

	// BITBUFFER.INC
	static IPluginFunction* s_BfWriteBoolFunc;
	static IPluginFunction* s_BfWriteByteFunc;
	static IPluginFunction* s_BfWriteCharFunc;
	static IPluginFunction* s_BfWriteShortFunc;
	static IPluginFunction* s_BfWriteWordFunc;
	static IPluginFunction* s_BfWriteNumFunc;
	static IPluginFunction* s_BfWriteFloatFunc;
	static IPluginFunction* s_BfWriteStringFunc;
	static IPluginFunction* s_BfWriteEntityFunc;
	static IPluginFunction* s_BfWriteAngleFunc;
	static IPluginFunction* s_BfWriteCoordFunc;
	static IPluginFunction* s_BfWriteVecCoordFunc;
	static IPluginFunction* s_BfWriteVecNormalFunc;
	static IPluginFunction* s_BfWriteAnglesFunc;
	static IPluginFunction* s_BfReadBoolFunc;
	static IPluginFunction* s_BfReadByteFunc;
	static IPluginFunction* s_BfReadCharFunc;
	static IPluginFunction* s_BfReadShortFunc;
	static IPluginFunction* s_BfReadWordFunc;
	static IPluginFunction* s_BfReadNumFunc;
	static IPluginFunction* s_BfReadFloatFunc;
	static IPluginFunction* s_BfReadStringFunc;
	static IPluginFunction* s_BfReadEntityFunc;
	static IPluginFunction* s_BfReadAngleFunc;
	static IPluginFunction* s_BfReadCoordFunc;
	static IPluginFunction* s_BfReadVecCoordFunc;
	static IPluginFunction* s_BfReadVecNormalFunc;
	static IPluginFunction* s_BfReadAnglesFunc;
	static IPluginFunction* s_BfGetNumBytesLeftFunc;

	// LOGGING.INC
	static IPluginFunction* s_LogMessageFunc;
	static IPluginFunction* s_LogToFileFunc;
	static IPluginFunction* s_LogToFileExFunc;
	static IPluginFunction* s_LogActionFunc;
	static IPluginFunction* s_LogErrorFunc;
	static IPluginFunction* s_AddGameLogHookFunc;
	static IPluginFunction* s_RemoveGameLogHookFunc;

	// SDKTOOLS_TEMPENTS.INC
	static IPluginFunction* s_AddTempEntHookFunc;
	static IPluginFunction* s_RemoveTempEntHookFunc;
	static IPluginFunction* s_TE_StartFunc;
	static IPluginFunction* s_TE_IsValidPropFunc;
	static IPluginFunction* s_TE_WriteNumFunc;
	static IPluginFunction* s_TE_ReadNumFunc;
	static IPluginFunction* s_TE_WriteFloatFunc;
	static IPluginFunction* s_TE_ReadFloatFunc;
	static IPluginFunction* s_TE_WriteVectorFunc;
	static IPluginFunction* s_TE_ReadVectorFunc;
	static IPluginFunction* s_TE_WriteAnglesFunc;
	static IPluginFunction* s_TE_WriteFloatArrayFunc;
	static IPluginFunction* s_TE_SendFunc;

	// SDKTOOLS_GAMERULES.INC
	static IPluginFunction* s_GameRules_GetPropFunc;
	static IPluginFunction* s_GameRules_SetPropFunc;
	static IPluginFunction* s_GameRules_GetPropFloatFunc;
	static IPluginFunction* s_GameRules_SetPropFloatFunc;
	static IPluginFunction* s_GameRules_GetPropEntFunc;
	static IPluginFunction* s_GameRules_SetPropEntFunc;
	static IPluginFunction* s_GameRules_GetPropVectorFunc;
	static IPluginFunction* s_GameRules_SetPropVectorFunc;
	static IPluginFunction* s_GameRules_GetPropStringFunc;
	static IPluginFunction* s_GameRules_SetPropStringFunc;

	// SDKTOOLS_ENTINPUT.INC
	static IPluginFunction* s_AcceptEntityInputFunc;

	// SDKTOOLS_ENTOUTPUT.INC
	static IPluginFunction* s_HookEntityOutputFunc;
	static IPluginFunction* s_UnhookEntityOutputFunc;
	static IPluginFunction* s_HookSingleEntityOutputFunc;
	static IPluginFunction* s_UnhookSingleEntityOutputFunc;
	static IPluginFunction* s_FireEntityOutputFunc;

	// HANDLES.INC
	static IPluginFunction* s_CloseHandleFunc;
	static IPluginFunction* s_CloneHandleFunc;

	// ENTITY_PROP_STOCKS.INC
	static IPluginFunction* s_GetEntityFlagsFunc;
	static IPluginFunction* s_SetEntityFlagsFunc;
	static IPluginFunction* s_GetEntityMoveTypeFunc;
	static IPluginFunction* s_SetEntityMoveTypeFunc;
	static IPluginFunction* s_GetEntityRenderModeFunc;
	static IPluginFunction* s_SetEntityRenderModeFunc;
	static IPluginFunction* s_GetEntityRenderFxFunc;
	static IPluginFunction* s_SetEntityRenderFxFunc;
	static IPluginFunction* s_GetEntityRenderColorFunc;
	static IPluginFunction* s_SetEntityRenderColorFunc;
	static IPluginFunction* s_GetEntityGravityFunc;
	static IPluginFunction* s_SetEntityGravityFunc;
	static IPluginFunction* s_SetEntityHealthFunc;
	static IPluginFunction* s_GetClientButtonsFunc;

	// HALFLIFE.INC
	static IPluginFunction* s_LogToGameFunc;
	static IPluginFunction* s_SetRandomSeedFunc;
	static IPluginFunction* s_IsMapValidFunc;
	static IPluginFunction* s_FindMapFunc;
	static IPluginFunction* s_GetMapDisplayNameFunc;
	static IPluginFunction* s_IsDedicatedServerFunc;
	static IPluginFunction* s_GetEngineTimeFunc;
	static IPluginFunction* s_GetGameTimeFunc;
	static IPluginFunction* s_GetGameTickCountFunc;
	static IPluginFunction* s_GetGameFrameTimeFunc;
	static IPluginFunction* s_GetGameDescriptionFunc;
	static IPluginFunction* s_GetGameFolderNameFunc;
	static IPluginFunction* s_GetCurrentMapFunc;
	static IPluginFunction* s_PrecacheModelFunc;
	static IPluginFunction* s_PrecacheSentenceFileFunc;
	static IPluginFunction* s_PrecacheDecalFunc;
	static IPluginFunction* s_PrecacheGenericFunc;
	static IPluginFunction* s_IsModelPrecachedFunc;
	static IPluginFunction* s_IsDecalPrecachedFunc;
	static IPluginFunction* s_IsGenericPrecachedFunc;
	static IPluginFunction* s_PrecacheSoundFunc;
	static IPluginFunction* s_CreateDialogFunc;
	static IPluginFunction* s_GetEngineVersionFunc;
	static IPluginFunction* s_PrintToChatFunc;
	static IPluginFunction* s_PrintCenterTextFunc;
	static IPluginFunction* s_PrintHintTextFunc;
	static IPluginFunction* s_ShowVGUIPanelFunc;
	static IPluginFunction* s_CreateHudSynchronizerFunc;
	static IPluginFunction* s_SetHudTextParamsFunc;
	static IPluginFunction* s_SetHudTextParamsExFunc;
	static IPluginFunction* s_ShowSyncHudTextFunc;
	static IPluginFunction* s_ClearSyncHudFunc;
	static IPluginFunction* s_ShowHudTextFunc;
	static IPluginFunction* s_EntIndexToEntRefFunc;
	static IPluginFunction* s_EntRefToEntIndexFunc;
	static IPluginFunction* s_MakeCompatEntRefFunc;
	static IPluginFunction* s_GetClientsInRangeFunc;
	static IPluginFunction* s_GetServerAuthIdFunc;
	static IPluginFunction* s_GetServerSteamAccountIdFunc;

	// TIMERS.INC
	static IPluginFunction* s_CreateTimerFunc;
	static IPluginFunction* s_KillTimerFunc;
	static IPluginFunction* s_TriggerTimerFunc;
	static IPluginFunction* s_GetTickedTimeFunc;
	static IPluginFunction* s_GetMapTimeLeftFunc;
	static IPluginFunction* s_GetMapTimeLimitFunc;
	static IPluginFunction* s_ExtendMapTimeLimitFunc;
	static IPluginFunction* s_GetTickIntervalFunc;
	static IPluginFunction* s_IsServerProcessingFunc;

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
	static IPluginFunction* s_FireEventToClientFunc;
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

using PM = PublicManager;
