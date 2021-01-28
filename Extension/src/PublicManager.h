#pragma once

#include "smsdk_ext.h"

#include "Defines.h"

#include <sstream>

/*static size_t UTIL_Format(char* buffer, size_t maxlength, const char* fmt, ...)
{
	va_list ap;
	va_start(ap, fmt);
	size_t len = vsnprintf(buffer, maxlength, fmt, ap);
	va_end(ap);

	if (len >= maxlength)
	{
		buffer[maxlength - 1] = '\0';
		return (maxlength - 1);
	}
	else
	{
		return len;
	}
}*/

#define DEFINE_PRINT_VARIADIC(NAME, FUNC) \
	static void NAME(int client, const char* message) { FUNC->PushCell(client); FUNC->PushString(message); cell_t res; FUNC->Execute(&res); }\
	\
	template<typename ... Param> \
	static void NAME(int client, const char* format, const Param& ... params) { FUNC->PushCell(client); std::string message = Format(format, params...); FUNC->PushString(message.c_str()); cell_t res; FUNC->Execute(&res); }

class PublicManager
{
public:
	static void InitOnPluginStart(IPluginContext* pContext);

	DEFINE_PRINT_VARIADIC(PrintToConsole, s_PrintToConsoleFunc)

	static void RegConsoleCmd(const char* command, const char* description, int flags);

	// CLIENT.INC
	static int GetMaxClients();
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
	static std::string Format(const char* format) { return format; }

	template<typename P1, typename ... Param>
	static std::string Format(const char* format, const P1& value, const Param& ... params)
	{
		std::string result;
		for (; *format != '\0'; format++)
		{
			if (*format == '%')
			{
				std::stringstream ss;
				ss << value;
				result += ss.str();
				result += Format(format + 2, params...);
				return result;
			}
			result += *format;
		}

		return result;
	}
private:
	static IPluginFunction* s_RegConsoleCmdFunc;
	static IPluginFunction* s_PrintToConsoleFunc;
	// CLIENTS.INC
	static IPluginFunction* s_GetMaxClientsFunc;
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
