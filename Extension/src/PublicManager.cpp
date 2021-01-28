#include "PublicManager.h"

IPluginFunction* PublicManager::s_RegConsoleCmdFunc = nullptr;
IPluginFunction* PublicManager::s_PrintToConsoleFunc = nullptr;

// CLIENT.INC
IPluginFunction* PublicManager::s_GetMaxClientsFunc = nullptr;
IPluginFunction* PublicManager::s_GetMaxHumanPlayersFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientCountFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientNameFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientIPFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientAuthIdFunc = nullptr;
IPluginFunction* PublicManager::s_GetSteamAccountIDFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientUserIdFunc = nullptr;
IPluginFunction* PublicManager::s_IsClientConnectedFunc = nullptr;
IPluginFunction* PublicManager::s_IsClientInGameFunc = nullptr;
IPluginFunction* PublicManager::s_IsClientInKickQueueFunc = nullptr;
IPluginFunction* PublicManager::s_IsClientAuthorizedFunc = nullptr;
IPluginFunction* PublicManager::s_IsFakeClientFunc = nullptr;
IPluginFunction* PublicManager::s_IsClientSourceTVFunc = nullptr;
IPluginFunction* PublicManager::s_IsClientReplayFunc = nullptr;
IPluginFunction* PublicManager::s_IsClientObserverFunc = nullptr;
IPluginFunction* PublicManager::s_IsPlayerAliveFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientInfoFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientTeamFunc = nullptr;
IPluginFunction* PublicManager::s_SetUserAdminFunc = nullptr;
IPluginFunction* PublicManager::s_GetUserAdminFunc = nullptr;
IPluginFunction* PublicManager::s_AddUserFlagsFunc = nullptr;
IPluginFunction* PublicManager::s_RemoveUserFlagsFunc = nullptr;
IPluginFunction* PublicManager::s_SetUserFlagBitsFunc = nullptr;
IPluginFunction* PublicManager::s_GetUserFlagBitsFunc = nullptr;
IPluginFunction* PublicManager::s_CanUserTargetFunc = nullptr;
IPluginFunction* PublicManager::s_RunAdminCacheChecksFunc = nullptr;
IPluginFunction* PublicManager::s_NotifyPostAdminCheckFunc = nullptr;
IPluginFunction* PublicManager::s_CreateFakeClientFunc = nullptr;
IPluginFunction* PublicManager::s_SetFakeClientConVarFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientHealthFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientModelFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientWeaponFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientMaxsFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientMinsFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientAbsAnglesFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientAbsOriginFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientArmorFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientDeathsFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientFragsFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientDataRateFunc = nullptr;
IPluginFunction* PublicManager::s_IsClientTimingOutFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientTimeFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientLatencyFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientAvgLatencyFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientAvgLossFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientAvgChokeFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientAvgDataFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientAvgPacketsFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientOfUserIdFunc = nullptr;
IPluginFunction* PublicManager::s_KickClientFunc = nullptr;
IPluginFunction* PublicManager::s_KickClientExFunc = nullptr;
IPluginFunction* PublicManager::s_ChangeClientTeamFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientSerialFunc = nullptr;
IPluginFunction* PublicManager::s_GetClientFromSerialFunc = nullptr;

#define STR(a) #a
#define LOAD_PTR(NAME) s_##NAME##Func = pContext->GetFunctionByName(STR(public_##NAME))

#include <typeinfo>

static int ExecFunc(IPluginFunction* func)
{
	int res;
	func->Execute(&res);
	return res;
}

static int ExecFunc(IPluginFunction* func, int p)
{
	func->PushCell(p);
	int res;
	func->Execute(&res);
	return res;
}

static int ExecFunc(IPluginFunction* func, int p1, int p2)
{
	func->PushCell(p1);
	func->PushCell(p2);
	int res;
	func->Execute(&res);
	return res;
}

static int ExecFunc(IPluginFunction* func, int p1, const char* p2)
{
	func->PushCell(p1);
	func->PushString(p2);
	int res;
	func->Execute(&res);
	return res;
}

static int ExecFunc(IPluginFunction* func, int p1, int p2, int p3)
{
	func->PushCell(p1);
	func->PushCell(p2);
	func->PushCell(p3);
	int res;
	func->Execute(&res);
	return res;
}

static int ExecFunc(IPluginFunction* func, const char* p)
{
	func->PushString(p);
	int res;
	func->Execute(&res);
	return res;
}

static int ExecFunc(IPluginFunction* func, int p1, float* p2)
{
	func->PushCell(p1);
	func->PushArray((int*)p2, 3);
	int res;
	func->Execute(&res);
	return res;
}

static int ExecFunc(IPluginFunction* func, int p1, const char* p2, int p3)
{
	func->PushCell(p1);
	func->PushString(p2);
	func->PushCell(p3);
	int res;
	func->Execute(&res);
	return res;
}

static int ExecFunc(IPluginFunction* func, int p1, const char* p2, const char* p3)
{
	func->PushCell(p1);
	func->PushString(p2);
	func->PushString(p3);
	int res;
	func->Execute(&res);
	return res;
}

static int ExecFunc(IPluginFunction* func, const char* p1, const char* p2, const char* p3)
{
	func->PushString(p1);
	func->PushString(p2);
	func->PushString(p3);
	int res;
	func->Execute(&res);
	return res;
}

void PublicManager::InitOnPluginStart(IPluginContext* pContext)
{
	s_RegConsoleCmdFunc = pContext->GetFunctionByName("public_RegConsoleCmd");
	s_PrintToConsoleFunc = pContext->GetFunctionByName("public_PrintToConsole");
	// CLIENT.INC
	LOAD_PTR(GetMaxClients);
	LOAD_PTR(GetMaxHumanPlayers);
	LOAD_PTR(GetClientCount);
	LOAD_PTR(GetClientName);
	LOAD_PTR(GetClientIP);
	LOAD_PTR(GetClientAuthId);
	LOAD_PTR(GetSteamAccountID);
	LOAD_PTR(GetClientUserId);
	LOAD_PTR(IsClientConnected);
	LOAD_PTR(IsClientInGame);
	LOAD_PTR(IsClientInKickQueue);
	LOAD_PTR(IsClientAuthorized);
	LOAD_PTR(IsFakeClient);
	LOAD_PTR(IsClientSourceTV);
	LOAD_PTR(IsClientReplay);
	LOAD_PTR(IsClientObserver);
	LOAD_PTR(IsPlayerAlive);
	LOAD_PTR(GetClientInfo);
	LOAD_PTR(GetClientTeam);
	LOAD_PTR(SetUserAdmin);
	LOAD_PTR(GetUserAdmin);
	LOAD_PTR(AddUserFlags);
	LOAD_PTR(RemoveUserFlags);
	LOAD_PTR(SetUserFlagBits);
	LOAD_PTR(GetUserFlagBits);
	LOAD_PTR(CanUserTarget);
	LOAD_PTR(RunAdminCacheChecks);
	LOAD_PTR(NotifyPostAdminCheck);
	LOAD_PTR(CreateFakeClient);
	LOAD_PTR(SetFakeClientConVar);
	LOAD_PTR(GetClientHealth);
	LOAD_PTR(GetClientModel);
	LOAD_PTR(GetClientWeapon);
	LOAD_PTR(GetClientMaxs);
	LOAD_PTR(GetClientMins);
	LOAD_PTR(GetClientAbsAngles);
	LOAD_PTR(GetClientAbsOrigin);
	LOAD_PTR(GetClientArmor);
	LOAD_PTR(GetClientDeaths);
	LOAD_PTR(GetClientFrags);
	LOAD_PTR(GetClientDataRate);
	LOAD_PTR(IsClientTimingOut);
	LOAD_PTR(GetClientTime);
	LOAD_PTR(GetClientLatency);
	LOAD_PTR(GetClientAvgLatency);
	LOAD_PTR(GetClientAvgLoss);
	LOAD_PTR(GetClientAvgChoke);
	LOAD_PTR(GetClientAvgData);
	LOAD_PTR(GetClientAvgPackets);
	LOAD_PTR(GetClientOfUserId);
	LOAD_PTR(KickClient);
	LOAD_PTR(KickClientEx);
	LOAD_PTR(ChangeClientTeam);
	LOAD_PTR(GetClientSerial);
	LOAD_PTR(GetClientFromSerial);
}

void PublicManager::RegConsoleCmd(const char* command, const char* description, int flags)
{
	s_RegConsoleCmdFunc->PushString("sm_test");
	s_RegConsoleCmdFunc->PushString("Testing");
	s_RegConsoleCmdFunc->PushCell(0);
	cell_t res;
	s_RegConsoleCmdFunc->Execute(&res);
}

int PublicManager::GetMaxClients()
{
	return ExecFunc(s_GetMaxClientsFunc);
}

int PublicManager::GetMaxHumanPlayers()
{
	cell_t res;
	s_GetMaxHumanPlayersFunc->Execute(&res);
	return res;
}

int PublicManager::GetClientCount(bool inGameOnly)
{
	s_GetClientCountFunc->PushCell(inGameOnly);
	cell_t res;
	s_GetClientCountFunc->Execute(&res);
	return res;
}

bool PublicManager::GetClientName(int client, char* name, int maxlen)
{
	s_GetClientNameFunc->PushCell(client);
	s_GetClientNameFunc->PushString(name);
	s_GetClientNameFunc->PushCell(maxlen);
	cell_t res;
	s_GetClientNameFunc->Execute(&res);
	return res;
}

bool PublicManager::GetClientIP(int client, char* ip, int maxlen, bool remport)
{
	s_GetClientIPFunc->PushCell(client);
	s_GetClientIPFunc->PushString(ip);
	s_GetClientIPFunc->PushCell(maxlen);
	s_GetClientIPFunc->PushCell(remport);
	cell_t res;
	s_GetClientIPFunc->Execute(&res);
	return res;
}

bool PublicManager::GetClientAuthId(int client, AuthIdType authType, char* auth, int maxlen, bool validate)
{
	s_GetClientAuthIdFunc->PushCell(client);
	s_GetClientAuthIdFunc->PushCell(authType);
	s_GetClientAuthIdFunc->PushString(auth);
	s_GetClientAuthIdFunc->PushCell(maxlen);
	s_GetClientAuthIdFunc->PushCell(validate);
	cell_t res;
	s_GetClientIPFunc->Execute(&res);
	return res;
}

int PublicManager::GetSteamAccountID(int client, bool validate)
{
	s_GetSteamAccountIDFunc->PushCell(client);
	s_GetSteamAccountIDFunc->PushCell(validate);
	cell_t res;
	s_GetSteamAccountIDFunc->Execute(&res);
	return res;
}

int PublicManager::GetClientUserId(int client)
{
	s_GetClientUserIdFunc->PushCell(client);
	cell_t res;
	s_GetClientUserIdFunc->Execute(&res);
	return res;
}

bool PublicManager::IsClientConnected(int client)
{
	s_IsClientConnectedFunc->PushCell(client);
	cell_t res;
	 s_IsClientConnectedFunc->Execute(&res);
	return res;
}

bool PublicManager::IsClientInGame(int client)
{
	s_IsClientInGameFunc->PushCell(client);
	cell_t res;
	s_IsClientInGameFunc->Execute(&res);
	return res;
}

bool PublicManager::IsClientInKickQueue(int client)
{
	s_IsClientInKickQueueFunc->PushCell(client);
	cell_t res;
	s_IsClientInKickQueueFunc->Execute(&res);
	return res;
}

bool PublicManager::IsClientAuthorized(int client)
{
	s_IsClientAuthorizedFunc->PushCell(client);
	cell_t res;
	s_IsClientAuthorizedFunc->Execute(&res);
	return res;
}

bool PublicManager::IsFakeClient(int client)
{
	s_IsFakeClientFunc->PushCell(client);
	cell_t res;
	s_IsFakeClientFunc->Execute(&res);
	return res;
}

bool PublicManager::IsClientSourceTV(int client)
{
	s_IsClientSourceTVFunc->PushCell(client);
	cell_t res;
	s_IsClientSourceTVFunc->Execute(&res);
	return res;
}

bool PublicManager::IsClientReplay(int client)
{
	s_IsClientReplayFunc->PushCell(client);
	cell_t res;
	s_IsClientReplayFunc->Execute(&res);
	return res;
}

bool PublicManager::IsClientObserver(int client)
{
	s_IsClientObserverFunc->PushCell(client);
	cell_t res;
	s_IsClientObserverFunc->Execute(&res);
	return res;
}

bool PublicManager::IsPlayerAlive(int client)
{
	s_IsPlayerAliveFunc->PushCell(client);
	cell_t res;
	s_IsPlayerAliveFunc->Execute(&res);
	return res;
}

bool PublicManager::GetClientInfo(int client, const char* key, char* value, int maxlen)
{
	s_GetClientInfoFunc->PushCell(client);
	s_GetClientInfoFunc->PushString(key);
	s_GetClientInfoFunc->PushString(value);
	s_GetClientInfoFunc->PushCell(maxlen);
	cell_t res;
	s_GetClientInfoFunc->Execute(&res);
	return res;
}

int PublicManager::GetClientTeam(int client)
{
	s_GetClientTeamFunc->PushCell(client);
	cell_t res;
	s_GetClientTeamFunc->Execute(&res);
	return res;
}

void PublicManager::SetUserAdmin(int client, AdminId id, bool temp)
{
	s_SetUserAdminFunc->PushCell(client);
	s_SetUserAdminFunc->PushCell(id);
	s_SetUserAdminFunc->PushCell(temp);
	cell_t res;
	s_SetUserAdminFunc->Execute(&res);
}

AdminId PublicManager::GetUserAdmin(int client)
{
	s_GetUserAdminFunc->PushCell(client);
	cell_t res;
	s_GetUserAdminFunc->Execute(&res);
	return res;
}

void PublicManager::AddUserFlags(int client, AdminFlag flag)
{
	s_AddUserFlagsFunc->PushCell(client);
	s_AddUserFlagsFunc->PushCell(flag);
	cell_t res;
	s_AddUserFlagsFunc->Execute(&res);
}

void PublicManager::RemoveUserFlags(int client, AdminFlag flag) { ExecFunc(s_RemoveUserFlagsFunc, client, flag); }

void PublicManager::SetUserFlagBits(int client, int flags) { ExecFunc(s_SetUserFlagBitsFunc, client, flags); }

int PublicManager::GetUserFlagBits(int client) { return ExecFunc(s_GetUserFlagBitsFunc, client); }

bool PublicManager::CanUserTarget(int client, int target) { return ExecFunc(s_CanUserTargetFunc, client, target); }

bool PublicManager::RunAdminCacheChecks(int client) { return ExecFunc(s_RunAdminCacheChecksFunc, client); }

void PublicManager::NotifyPostAdminCheck(int client) { ExecFunc(s_NotifyPostAdminCheckFunc, client); }

int PublicManager::CreateFakeClient(const char* name) { return ExecFunc(s_CreateFakeClientFunc, name); }

void PublicManager::SetFakeClientConVar(int client, const char* cvar, const char* value) { ExecFunc(s_SetFakeClientConVarFunc, client, cvar, value); }

int PublicManager::GetClientHealth(int client) { return ExecFunc(s_GetClientHealthFunc, client); }

void PublicManager::GetClientModel(int client, char* model, int maxlen) { ExecFunc(s_GetClientModelFunc, client, model, maxlen); }

void PublicManager::GetClientWeapon(int client, char* weapon, int maxlen) { ExecFunc(s_GetClientWeaponFunc, client, weapon, maxlen); }

void PublicManager::GetClientMaxs(int client, float vec[3]) { ExecFunc(s_GetClientMaxsFunc, client, vec); }

void PublicManager::GetClientMins(int client, float vec[3]) { ExecFunc(s_GetClientMinsFunc, client, vec); }

void PublicManager::GetClientAbsAngles(int client, float ang[3]) { ExecFunc(s_GetClientAbsAnglesFunc, client, ang); }

void PublicManager::GetClientAbsOrigin(int client, float vec[3]) { ExecFunc(s_GetClientAbsOriginFunc, client, vec); }

int PublicManager::GetClientArmor(int client) { return ExecFunc(s_GetClientArmorFunc, client); }

int PublicManager::GetClientDeaths(int client) { return ExecFunc(s_GetClientDeathsFunc, client); }

int PublicManager::GetClientFrags(int client) { return ExecFunc(s_GetClientFragsFunc, client); }

int PublicManager::GetClientDataRate(int client) { return ExecFunc(s_GetClientDataRateFunc, client); }

bool PublicManager::IsClientTimingOut(int client) { return ExecFunc(s_IsClientTimingOutFunc, client); }

float PublicManager::GetClientTime(int client) { return sp_ctof(ExecFunc(s_GetClientTimeFunc, client)); }

float PublicManager::GetClientLatency(int client, NetFlow flow) { return sp_ctof(ExecFunc(s_GetClientLatencyFunc, client, flow)); }

float PublicManager::GetClientAvgLatency(int client, NetFlow flow) { return sp_ctof(ExecFunc(s_GetClientAvgLatencyFunc, client, flow)); }

float PublicManager::GetClientAvgLoss(int client, NetFlow flow) { return sp_ctof(ExecFunc(s_GetClientAvgLossFunc, client, flow)); }

float PublicManager::GetClientAvgChoke(int client, NetFlow flow) { return sp_ctof(ExecFunc(s_GetClientAvgChokeFunc, client, flow)); }

float PublicManager::GetClientAvgData(int client, NetFlow flow) { return sp_ctof(ExecFunc(s_GetClientAvgDataFunc, client, flow)); }

float PublicManager::GetClientAvgPackets(int client, NetFlow flow) { return sp_ctof(ExecFunc(s_GetClientAvgPacketsFunc, client, flow)); }

int PublicManager::GetClientOfUserId(int userid) { return ExecFunc(s_GetClientOfUserIdFunc, userid); }

void PublicManager::KickClient(int client, const char* message) { ExecFunc(s_KickClientFunc, client, message); }

void PublicManager::KickClientEx(int client, const char* message) { ExecFunc(s_KickClientExFunc, client, message); }

void PublicManager::ChangeClientTeam(int client, int team) { ExecFunc(s_ChangeClientTeamFunc, client, team); }

int PublicManager::GetClientSerial(int client) { return ExecFunc(s_GetClientSerialFunc, client); }

int PublicManager::GetClientFromSerial(int serial) { return ExecFunc(s_GetClientFromSerialFunc, serial); }
