#pragma once

#include "smsdk_ext.h"

#include "Defines.h"

#include <sstream>
#include <unordered_map>

#define VARIADIC_FUNC2(FUNC, FUNC_IMPL, T1) \
	static void FUNC(T1 client) { PushArg(FUNC_IMPL, client); ExecFunc(FUNC_IMPL); } \
	template<typename ... Args> \
	static void FUNC(T1 client, Args ... args) { PushArg(FUNC_IMPL, client); FUNC##Sub(args...); } \
	private: \
	template<typename P1, typename ... Args> \
	static void FUNC##Sub(P1 p1, Args ... args) { PushArgRef(FUNC_IMPL, p1); FUNC##Sub(args...); } \
	static void FUNC##Sub(int& arg) { PushArgRef(FUNC_IMPL, arg); ExecFunc(FUNC_IMPL); } \
	static void FUNC##Sub(float& arg) { PushArgRef(FUNC_IMPL, arg); ExecFunc(FUNC_IMPL); } \
	static void FUNC##Sub(const char* arg) { PushArg(FUNC_IMPL, arg); ExecFunc(FUNC_IMPL); } \
	public:

#define VARIADIC_FUNC3(FUNC, FUNC_IMPL, T1, T2) \
	static void FUNC(T1 client, T2 message) { PushArg(FUNC_IMPL, client); PushArg(FUNC_IMPL, message); ExecFunc(FUNC_IMPL); } \
	template<typename ... Args> \
	static void FUNC(T1 client, T2 format, Args ... args) { PushArg(FUNC_IMPL, client); PushArg(FUNC_IMPL, format); FUNC##Sub(args...); } \
	private: \
	template<typename P1, typename ... Args> \
	static void FUNC##Sub(P1 p1, Args ... args) { PushArgRef(FUNC_IMPL, p1); FUNC##Sub(args...); } \
	static void FUNC##Sub(int& arg) { PushArgRef(FUNC_IMPL, arg); ExecFunc(FUNC_IMPL); } \
	static void FUNC##Sub(float& arg) { PushArgRef(FUNC_IMPL, arg); ExecFunc(FUNC_IMPL); } \
	static void FUNC##Sub(const char* arg) { PushArg(FUNC_IMPL, arg); ExecFunc(FUNC_IMPL); } \
	public:

#define VARIADIC_FUNC4(FUNC, FUNC_IMPL, T1, T2, T3) \
	static void FUNC(T1 client, T2 message, T3 arg3) { PushArg(FUNC_IMPL, client); PushArg(FUNC_IMPL, message); PushArg(FUNC_IMPL, arg3); ExecFunc(FUNC_IMPL); } \
	template<typename ... Args> \
	static void FUNC(T1 client, T2 format, T3 arg3, Args ... args) { PushArg(FUNC_IMPL, client); PushArg(FUNC_IMPL, format); PushArg(FUNC_IMPL, arg3); FUNC##Sub(args...); } \
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

using SQLTxnSuccessFunc = void (*)(database_t db, int data, int numQueries, DBResultSet results[], int queryData[]);
using SQLTxnFailureFunc = void(*)(database_t db, int data, int numQueries, const char* error, int failIndex, int queryData[]);
using SQLTCallbackFunc = void(*)(Handle owner, Handle hndl, const char* error, int data);
using EventHookCallback = Action(*)(EventHandle eventHandle, const char* name, bool dontBroadcast);

class PublicManager
{
public:
	static void InitOnPluginStart(IPluginContext* pContext);

	// EVENTS.INC
	static void HookEvent(EventHookCallback callback, const char* name, EventHookMode mode)
	{
		rootconsole->ConsolePrint("Hooking %s %d", name, mode);

		if (mode == EventHookMode::EventHookMode_Pre)
			s_EventHookCallbacksPre[name] = callback;
		else if (mode == EventHookMode::EventHookMode_PostNoCopy)
			s_EventHookCallbacksPostNoCopy[name] = callback;
		else
		{
			s_EventHookCallbacksPost[name] = callback;
			mode = EventHookMode::EventHookMode_Post;
		}

		ExecFunc(s_HookEventFunc, name, mode);
	}
	static bool HookEventEx(EventHookCallback callback, const char* name, EventHookMode mode)
	{
		if (mode == EventHookMode::EventHookMode_Pre)
			s_EventHookCallbacksPre[name] = callback;
		else if (mode == EventHookMode::EventHookMode_PostNoCopy)
			s_EventHookCallbacksPostNoCopy[name] = callback;
		else
		{
			s_EventHookCallbacksPost[name] = callback;
			mode = EventHookMode::EventHookMode_Post;
		}

		return ExecFunc(s_HookEventExFunc, name, mode);
	}
	static void UnhookEvent(const char* name, EventHookMode mode) { ExecFunc(s_UnhookEventFunc, name, mode); }
	static EventHandle CreateEvent(const char* name, bool force) { return ExecFunc(s_CreateEventFunc, name, force); }
	static void FireEvent(Handle eventHandle, bool dontBroadcast) { ExecFunc(s_FireEventFunc, eventHandle, dontBroadcast); }
	static void CancelCreatedEvent(Handle eventHandle) { ExecFunc(s_CancelCreatedEventFunc, eventHandle); }
	static bool GetEventBool(Handle eventHandle, const char* key, bool defValue) { return ExecFunc(s_GetEventBoolFunc, eventHandle, key, defValue); }
	static void SetEventBool(Handle eventHandle, const char* key, bool value) { ExecFunc(s_SetEventBoolFunc, eventHandle, key, value); }
	static int GetEventInt(Handle eventHandle, const char* key, int defValue) { return ExecFunc(s_GetEventIntFunc, eventHandle, key, defValue); }
	static void SetEventInt(Handle eventHandle, const char* key, int value) { ExecFunc(s_SetEventIntFunc, eventHandle, key, value); }
	static float GetEventFloat(Handle eventHandle, const char* key, float defValue) { return ExecFunc(s_GetEventFloatFunc, eventHandle, key, defValue); }
	static void SetEventFloat(Handle eventHandle, const char* key, float value) { ExecFunc(s_SetEventFloatFunc, eventHandle, key, value); }
	static void GetEventString(Handle eventHandle, const char* key, char* value, int maxlength, const char* defValue) { ExecFunc(s_GetEventStringFunc, eventHandle, key, value, maxlength, defValue); }
	static void SetEventString(Handle eventHandle, const char* key, const char* value) { ExecFunc(s_SetEventStringFunc, eventHandle, key, value); }
	static void GetEventName(Handle eventHandle, char* name, int maxlength) { ExecFunc(s_GetEventNameFunc, eventHandle, name, maxlength); }
	static void SetEventBroadcast(Handle eventHandle, bool dontBroadcast) { ExecFunc(s_SetEventBroadcastFunc, eventHandle, dontBroadcast); }

	// DBI.INC
	static database_t SQL_Connect(const char* confname, bool persistent, char* error, int maxlength) { return ExecFunc(s_SQL_ConnectFunc, confname, persistent, error, maxlength); }
	static database_t SQL_ConnectCustom(Handle keyvalues, char* error, int maxlength, bool persistent) { return ExecFunc(s_SQL_ConnectCustomFunc, keyvalues, error, maxlength, persistent); }
	static bool SQL_CheckConfig(const char* name) { return ExecFunc(s_SQL_CheckConfigFunc, name); }
	static DBDriver SQL_GetDriver(const char* name) { return ExecFunc(s_SQL_GetDriverFunc, name); }
	static DBDriver SQL_ReadDriver(Handle database, char* ident, int ident_length) { return ExecFunc(s_SQL_ReadDriverFunc, database, ident, ident_length); }
	static void SQL_GetDriverIdent(Handle driver, char* ident, int maxlength) { ExecFunc(s_SQL_GetDriverIdentFunc, driver, ident, maxlength); }
	static void SQL_GetDriverProduct(Handle driver, char* product, int maxlength) { ExecFunc(s_SQL_GetDriverProductFunc, driver, product, maxlength); }
	static bool SQL_SetCharset(Handle database, const char* charset) { return ExecFunc(s_SQL_SetCharsetFunc, database, charset); }
	static int SQL_GetAffectedRows(Handle hndl) { return ExecFunc(s_SQL_GetAffectedRowsFunc, hndl); }
	static int SQL_GetInsertId(Handle hndl) { return ExecFunc(s_SQL_GetInsertIdFunc, hndl); }
	static bool SQL_GetError(Handle hndl, char* error, int maxlength) { return ExecFunc(s_SQL_GetErrorFunc, hndl, error, maxlength); }
	static bool SQL_EscapeString(Handle database, const char* string, char* buffer, int maxlength, int& written)
	{
		PushArg(s_SQL_EscapeStringFunc, database); PushArg(s_SQL_EscapeStringFunc, string);
		PushArg(s_SQL_EscapeStringFunc, buffer); PushArg(s_SQL_EscapeStringFunc, maxlength);
		PushArgRef(s_SQL_EscapeStringFunc, written);
		return ExecAndReturn(s_SQL_EscapeStringFunc);
	}
	VARIADIC_FUNC5(SQL_FormatQuery, s_SQL_FormatQueryFunc, Handle, const char*, int, const char*)
	static bool SQL_FastQuery(Handle database, const char* query, int len) { return ExecFunc(s_SQL_FastQueryFunc, database, query, len); }
	static DBResultSet SQL_Query(Handle database, const char* query, int len) { return ExecFunc(s_SQL_QueryFunc, database, query, len); }
	static DBStatement SQL_PrepareQuery(Handle database, const char* query, char* error, int maxlength) { return ExecFunc(s_SQL_PrepareQueryFunc, database, query, error, maxlength); }
	static bool SQL_FetchMoreResults(Handle query) { return ExecFunc(s_SQL_FetchMoreResultsFunc, query); }
	static bool SQL_HasResultSet(Handle query) { return ExecFunc(s_SQL_HasResultSetFunc, query); }
	static int SQL_GetRowCount(Handle query) { return ExecFunc(s_SQL_GetRowCountFunc, query); }
	static int SQL_GetFieldCount(Handle query) { return ExecFunc(s_SQL_GetFieldCountFunc, query); }
	static void SQL_FieldNumToName(Handle query, int field, char* name, int maxlength) { ExecFunc(s_SQL_FieldNumToNameFunc, query, field, name, maxlength); }
	static bool SQL_FieldNameToNum(Handle query, const char* name, int& field)
	{
		PushArg(s_SQL_FieldNameToNumFunc, query); PushArg(s_SQL_FieldNameToNumFunc, name); PushArgRef(s_SQL_FieldNameToNumFunc, field);
		return ExecAndReturn(s_SQL_FieldNameToNumFunc);
	}
	static bool SQL_FetchRow(Handle query) { return ExecFunc(s_SQL_FetchRowFunc, query); }
	static bool SQL_MoreRows(Handle query) { return ExecFunc(s_SQL_MoreRowsFunc, query); }
	static bool SQL_Rewind(Handle query) { return ExecFunc(s_SQL_RewindFunc, query); }
	static int SQL_FetchString(Handle query, int field, char* buffer, int maxlength, DBResult& result)
	{
		PushArg(s_SQL_FetchStringFunc, query); PushArg(s_SQL_FetchStringFunc, field); PushArg(s_SQL_FetchStringFunc, buffer);
		PushArg(s_SQL_FetchStringFunc, maxlength); PushArgRef(s_SQL_FetchStringFunc, reinterpret_cast<int&>(result));
		return ExecFunc(s_SQL_FetchStringFunc, query, field, buffer, maxlength, result);
	}
	static float SQL_FetchFloat(Handle query, int field, DBResult& result)
	{
		PushArg(s_SQL_FetchFloatFunc, query); PushArg(s_SQL_FetchFloatFunc, field); PushArgRef(s_SQL_FetchFloatFunc, reinterpret_cast<int&>(result));
		return ExecAndReturn(s_SQL_FetchFloatFunc);
	}
	static int SQL_FetchInt(Handle query, int field, DBResult& result)
	{
		PushArg(s_SQL_FetchIntFunc, query); PushArg(s_SQL_FetchIntFunc, field); PushArgRef(s_SQL_FetchIntFunc, reinterpret_cast<int&>(result));
		return ExecAndReturn(s_SQL_FetchIntFunc);
	}
	static bool SQL_IsFieldNull(Handle query, int field) { return ExecFunc(s_SQL_IsFieldNullFunc, query, field); }
	static int SQL_FetchSize(Handle query, int field) { return ExecFunc(s_SQL_FetchSizeFunc, query, field); }
	static void SQL_BindParamInt(Handle statement, int param, int number, bool isSigned) { ExecFunc(s_SQL_BindParamStringFunc, statement, param, number, isSigned); }
	static void SQL_BindParamFloat(Handle statement, int param, float value) { ExecFunc(s_SQL_BindParamFloatFunc, statement, param, value); }
	static void SQL_BindParamString(Handle statement, int param, const char* value, bool copy) { ExecFunc(s_SQL_BindParamStringFunc, statement, param, value, copy); }
	static bool SQL_Execute(Handle statement) { return ExecFunc(s_SQL_ExecuteFunc, statement); }
	static void SQL_LockDatabase(Handle database) { ExecFunc(s_SQL_LockDatabaseFunc, database); }
	static void SQL_UnlockDatabase(Handle database) { ExecFunc(s_SQL_UnlockDatabaseFunc, database); }
	static void SQL_TConnect(SQLTCallbackFunc callback, const char* name, int data)
	{
		static int index = 0;
		s_SQLTConnectCallbacksData[index] = data;
		s_SQLTConnectCallbacks[index] = callback;
		ExecFunc(s_SQL_TConnectFunc, name, index);
		++index;
	}
	static void SQL_TQuery(SQLTCallbackFunc callback, Handle database, const char* query, int data, DBPriority prio)
	{
		static int index = 0;
		s_SQLTQueryCallbacksData[index] = data;
		s_SQLTQueryCallbacks[index] = callback;
		ExecFunc(s_SQL_TQueryFunc, database, query, data, prio);
		++index;
	}
	static transaction_t SQL_CreateTransaction() { return ExecFunc(s_SQL_CreateTransactionFunc); }
	static int SQL_AddQuery(transaction_t txn, const char* query, int data) { return ExecFunc(s_SQL_AddQueryFunc, txn, query, data); }
	static void SQL_ExecuteTransaction(Handle db, transaction_t txn, int data, DBPriority priority) { ExecFunc(s_SQL_ExecuteTransactionFunc, db, txn, data, priority); }

	// CSTIKE.INC
	static void CS_RespawnPlayer(int client);
	static void CS_SwitchTeam(int client, int team);
	static void CS_DropWeapon(int client, int weaponIndex, bool toss, bool blockhook);
	static void CS_TerminateRound(float delay, CSRoundEndReason reason, bool blockhook);
	static void CS_GetTranslatedWeaponAlias(const char* alias, char* weapon, int size);
	static int CS_GetWeaponPrice(int client, CSWeaponID id, bool defaultprice);
	static int CS_GetClientClanTag(int client, char* buffer, int size);
	static void CS_SetClientClanTag(int client, const char* tag);
	static int CS_GetTeamScore(int team);
	static void CS_SetTeamScore(int team, int value);
	static int CS_GetMVPCount(int client);
	static void CS_SetMVPCount(int client, int value);
	static int CS_GetClientContributionScore(int client);
	static void CS_SetClientContributionScore(int client, int value);
	static int CS_GetClientAssists(int client);
	static void CS_SetClientAssists(int client, int value);
	static CSWeaponID CS_AliasToWeaponID(const char* alias);
	static int CS_WeaponIDToAlias(CSWeaponID weaponID, char* destination, int len);
	static bool CS_IsValidWeaponID(CSWeaponID id);
	static void CS_UpdateClientModel(int client);
	static CSWeaponID CS_ItemDefIndexToID(int iDefIndex);
	static int CS_WeaponIDToItemDefIndex(CSWeaponID id);

	// CONSOLE.INC
	VARIADIC_FUNC2(ServerCommand, s_ServerCommandFunc, const char*)
	VARIADIC_FUNC4(ServerCommandEx, s_ServerCommandExFunc, char*, int, const char*);
	VARIADIC_FUNC2(InsertServerCommand, s_InsertServerCommandFunc, const char*)
	static void ServerExecute();
	VARIADIC_FUNC3(ClientCommand, s_ClientCommandFunc, int, const char*);
	VARIADIC_FUNC3(FakeClientCommand, s_FakeClientCommandFunc, int, const char*);
	VARIADIC_FUNC3(FakeClientCommandEx, s_FakeClientCommandExFunc, int, const char*);
	static void FakeClientCommandKeyValues(int client, KeyValuesHandle kv) { ExecFunc(s_FakeClientCommandKeyValuesFunc, client, kv); }
	VARIADIC_FUNC2(PrintToServer, s_PrintToServerFunc, const char*);
	VARIADIC_FUNC3(PrintToConsole, s_PrintToConsoleFunc, int, const char*)
	VARIADIC_FUNC3(ReplyToCommand, s_ReplyToCommandFunc, int, const char*)
	static ReplySource GetCmdReplySource();
	static ReplySource SetCmdReplySource(ReplySource source);
	static bool IsChatTrigger();
	VARIADIC_FUNC4(ShowActivity2, s_ShowActivity2Func, int, const char*, const char*);
	VARIADIC_FUNC3(ShowActivity, s_ShowActivityFunc, int, const char*);
	VARIADIC_FUNC4(ShowActivityEx, s_ShowActivityExFunc, int, const char*, const char*);
	static bool FormatActivitySource(int client, int target, const char* namebuf, int maxlength);
	static void RegServerCmd(const char* cmd, const char* description, int flags);
	static void RegConsoleCmd(const char* cmd, const char* description, int flags);
	static void RegAdminCmd(const char* cmd, int adminflags, const char* description, const char* group, int flags);
	static int GetCmdArgs();
	static int GetCmdArg(int argnum, char* buffer, int maxlength);
	static int GetCmdArgString(char* buffer, int maxlength);
	static Handle GetCommandIterator();
	static bool ReadCommandIterator(Handle iter, char* name, int nameLen, int& eflags, char* desc, int descLen);
	static bool CheckCommandAccess(int client, const char* command, int flags, bool override_only);
	static bool CheckAccess(AdminId id, const char* command, int flags, bool override_only);
	static int GetCommandFlags(const char* name);
	static bool SetCommandFlags(const char* name, int flags);
	static Handle FindFirstConCommand(char* buffer, int max_size, bool& isCommand, int& flags, char* description, int descrmax_size);
	static bool FindNextConCommand(Handle search, char* buffer, int max_size, bool& isCommand, int& flags, char* description, int descrmax_size);
	static void AddServerTag(const char* tag);
	static void RemoveServerTag(const char* tag);
	static bool AddCommandListener(const char* command);
	static void RemoveCommandListener(const char* command);

	// CLIENT.INC
	static int GetMaxClients() { return s_MaxClients; }
	static int GetMaxHumanPlayers();
	static int GetClientCount(bool inGameOnly);
	static bool GetClientName(int client, char* name, int maxlen);
	static bool GetClientIP(int client, char* ip, int maxlen, bool remport);
	static bool GetClientAuthId(int client, AuthIdType authType, char* auth, int maxlen, bool validate);
	static int GetSteamAccountID(int client, bool validate);
	static int GetClientUserId(int client);
	static bool IsClientConnected(int client);
	static bool IsClientInGame(int client);
	static bool IsClientInKickQueue(int client);
	static bool IsClientAuthorized(int client);
	static bool IsFakeClient(int client);
	static bool IsClientSourceTV(int client);
	static bool IsClientReplay(int client);
	static bool IsClientObserver(int client);
	static bool IsPlayerAlive(int client);
	static bool GetClientInfo(int client, const char* key, char* value, int maxlen);
	static int GetClientTeam(int client);
	static void SetUserAdmin(int client, AdminId id, bool temp);
	static AdminId GetUserAdmin(int client);
	static void AddUserFlags(int client, AdminFlag flag); // TODO: AdminFlag ... flags
	static void RemoveUserFlags(int client, AdminFlag flag); // TODO: AdminFlag ... flags
	static void SetUserFlagBits(int client, int flags);
	static int GetUserFlagBits(int client);
	static bool CanUserTarget(int client, int target);
	static bool RunAdminCacheChecks(int client);
	static void NotifyPostAdminCheck(int client);
	static int CreateFakeClient(const char* name);
	static void SetFakeClientConVar(int client, const char* cvar, const char* value);
	static int GetClientHealth(int client);
	static void GetClientModel(int client, char* model, int maxlen);
	static void GetClientWeapon(int client, char* weapon, int maxlen);
	static void GetClientMaxs(int client, float vec[3]);
	static void GetClientMins(int client, float vec[3]);
	static void GetClientAbsAngles(int client, float ang[3]);
	static void GetClientAbsOrigin(int client, float vec[3]);
	static int GetClientArmor(int client);
	static int GetClientDeaths(int client);
	static int GetClientFrags(int client);
	static int GetClientDataRate(int client);
	static bool IsClientTimingOut(int client);
	static float GetClientTime(int client);
	static float GetClientLatency(int client, NetFlow flow);
	static float GetClientAvgLatency(int client, NetFlow flow);
	static float GetClientAvgLoss(int client, NetFlow flow);
	static float GetClientAvgChoke(int client, NetFlow flow);
	static float GetClientAvgData(int client, NetFlow flow);
	static float GetClientAvgPackets(int client, NetFlow flow);
	static int GetClientOfUserId(int userid);
	static void KickClient(int client, const char* message);
	static void KickClientEx(int client, const char* message);
	static void ChangeClientTeam(int client, int team);
	static int GetClientSerial(int client);
	static int GetClientFromSerial(int serial);
private:
	static void PushArg(IPluginFunction* func, int arg) { func->PushCell(arg); }
	static void PushArg(IPluginFunction* func, float arg) { func->PushFloat(arg); }
	static void PushArg(IPluginFunction* func, const char* arg) { func->PushString(arg); }
	static void PushArg(IPluginFunction* func, float arg[3]) { func->PushArray((int*)arg, 3, 1); }

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
private:
	friend class NativeManager;

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