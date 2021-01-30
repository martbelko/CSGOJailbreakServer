#pragma once

#include "smsdk_ext.h"

#include "Defines.h"

#include <sstream>

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

/*
public void public_CS_RespawnPlayer(int client);
public void public_CS_SwitchTeam(int client, int team);
public void public_CS_DropWeapon(int client, int weaponIndex, bool toss, bool blockhook);
public void public_CS_TerminateRound(float delay, CSRoundEndReason reason, bool blockhook);
public void public_CS_GetTranslatedWeaponAlias(const char[] alias, char[] weapon, int size);
public int public_CS_GetWeaponPrice(int client, CSWeaponID id, bool defaultprice);
public int public_CS_GetClientClanTag(int client, char[] buffer, int size);
public void public_CS_SetClientClanTag(int client, const char[] tag);
public int public_CS_GetTeamScore(int team);
public void public_CS_SetTeamScore(int team, int value);
public int public_CS_GetMVPCount(int client);
public void public_CS_SetMVPCount(int client, int value);
public int public_CS_GetClientContributionScore(int client);
public void public_CS_SetClientContributionScore(int client, int value);
public int public_CS_GetClientAssists(int client);
public void public_CS_SetClientAssists(int client, int value);
public CSWeaponID public_CS_AliasToWeaponID(const char[] alias);
public int public_CS_WeaponIDToAlias(CSWeaponID weaponID, char[] destination, int len);
public bool public_CS_IsValidWeaponID(CSWeaponID id);
public void public_CS_UpdateClientModel(int client);
public CSWeaponID public_CS_ItemDefIndexToID(int iDefIndex);
public int public_CS_WeaponIDToItemDefIndex(CSWeaponID id);
*/

class PublicManager
{
public:
	static void InitOnPluginStart(IPluginContext* pContext);

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
	//static void FakeClientCommandKeyValues(int client, KeyValues kv);
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
	static int s_MaxClients;

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
