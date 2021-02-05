public:
	static int GetMaxHumanPlayers()
	{
		return ExecFunc(s_GetMaxHumanPlayersFunc);
	}

	static int GetClientCount(bool inGameOnly)
	{
		return ExecFunc(s_GetClientCountFunc, inGameOnly);
	}

	static bool GetClientName(int client, char* name, int maxlen)
	{
		s_GetClientNameFunc->PushCell(client);
		s_GetClientNameFunc->PushStringEx(name, maxlen, 0, 1);
		s_GetClientNameFunc->PushCell(maxlen);
		return ExecAndReturn(s_GetClientNameFunc);
	}

	static bool GetClientIP(int client, char* ip, int maxlen, bool remport)
	{
		s_GetClientIPFunc->PushCell(client);
		s_GetClientIPFunc->PushStringEx(ip, maxlen, 0, 1);
		s_GetClientIPFunc->PushCell(maxlen);
		s_GetClientIPFunc->PushCell(remport);
		return ExecAndReturn(s_GetClientIPFunc);
	}

	static bool GetClientAuthId(int client, AuthIdType authType, char* auth, int maxlen, bool validate)
	{
		s_GetClientAuthIdFunc->PushCell(client);
		s_GetClientAuthIdFunc->PushCell(authType);
		s_GetClientAuthIdFunc->PushStringEx(auth, maxlen, 0, 1);
		s_GetClientAuthIdFunc->PushCell(maxlen);
		s_GetClientAuthIdFunc->PushCell(validate);
		return ExecAndReturn(s_GetClientAuthIdFunc);
	}

	static int GetSteamAccountID(int client, bool validate)
	{
		return ExecFunc(s_GetSteamAccountIDFunc, client, validate);
	}

	static int GetClientUserId(int client)
	{
		return ExecFunc(s_GetClientUserIdFunc, client);
	}

	static bool IsClientConnected(int client)
	{
		return ExecFunc(s_IsClientConnectedFunc, client);
	}

	static bool IsClientInGame(int client)
	{
		return ExecFunc(s_IsClientInGameFunc, client);
	}

	static bool IsClientInKickQueue(int client)
	{
		return ExecFunc(s_IsClientInKickQueueFunc, client);
	}

	static bool IsClientAuthorized(int client)
	{
		return ExecFunc(s_IsClientAuthorizedFunc, client);
	}

	static bool IsFakeClient(int client)
	{
		return ExecFunc(s_IsFakeClientFunc, client);
	}

	static bool IsClientSourceTV(int client)
	{
		return ExecFunc(s_IsClientSourceTVFunc, client);
	}

	static bool IsClientReplay(int client)
	{
		return ExecFunc(s_IsClientReplayFunc, client);
	}

	static bool IsClientObserver(int client)
	{
		return ExecFunc(s_IsClientObserverFunc, client);
	}

	static bool IsPlayerAlive(int client)
	{
		return ExecFunc(s_IsPlayerAliveFunc, client);
	}

	static bool GetClientInfo(int client, const char* key, char* value, int maxlen)
	{
		s_GetClientInfoFunc->PushCell(client);
		s_GetClientInfoFunc->PushString(key);
		s_GetClientInfoFunc->PushStringEx(value, maxlen, 0, 1);
		s_GetClientInfoFunc->PushCell(maxlen);
		return ExecAndReturn(s_GetClientInfoFunc);
	}

	static int GetClientTeam(int client)
	{
		return ExecFunc(s_GetClientTeamFunc, client);
	}

	static void SetUserAdmin(int client, AdminId id, bool temp)
	{
		ExecFunc(s_SetUserAdminFunc, client, id, temp);
	}

	static AdminId GetUserAdmin(int client)
	{
		return ExecFunc(s_GetUserAdminFunc, client);
	}

	static void SetUserFlagBits(int client, int flags)
	{
		ExecFunc(s_SetUserFlagBitsFunc, client, flags);
	}

	static int GetUserFlagBits(int client)
	{
		return ExecFunc(s_GetUserFlagBitsFunc, client);
	}

	static bool CanUserTarget(int client, int target)
	{
		return ExecFunc(s_CanUserTargetFunc, client, target);
	}

	static bool RunAdminCacheChecks(int client)
	{
		return ExecFunc(s_RunAdminCacheChecksFunc, client);
	}

	static void NotifyPostAdminCheck(int client)
	{
		ExecFunc(s_NotifyPostAdminCheckFunc, client);
	}

	static int CreateFakeClient(const char* name)
	{
		return ExecFunc(s_CreateFakeClientFunc, name);
	}

	static void SetFakeClientConVar(int client, const char* cvar, const char* value)
	{
		ExecFunc(s_SetFakeClientConVarFunc, client, cvar, value);
	}

	static int GetClientHealth(int client)
	{
		return ExecFunc(s_GetClientHealthFunc, client);
	}
	static void GetClientModel(int client, char* model, int maxlen)
	{
		PushArg(s_GetClientModelFunc, client);
		s_GetClientModelFunc->PushStringEx(model, maxlen, 0, 1);
		PushArg(s_GetClientModelFunc, maxlen);
		ExecAndReturn(s_GetClientModelFunc);
	}

	static void GetClientWeapon(int client, char* weapon, int maxlen)
	{
		PushArg(s_GetClientWeaponFunc, client);
		s_GetClientWeaponFunc->PushStringEx(weapon, maxlen, 0, 1);
		PushArg(s_GetClientWeaponFunc, maxlen);
		ExecAndReturn(s_GetClientWeaponFunc);
	}

	static void GetClientMaxs(int client, float vec[3])
	{
		ExecFunc(s_GetClientMaxsFunc, client, vec);
	}

	static void GetClientMins(int client, float vec[3])
	{
		ExecFunc(s_GetClientMinsFunc, client, vec);
	}

	static void GetClientAbsAngles(int client, float ang[3])
	{
		ExecFunc(s_GetClientAbsAnglesFunc, client, ang);
	}

	static void GetClientAbsOrigin(int client, float vec[3])
	{
		ExecFunc(s_GetClientAbsOriginFunc, client, vec);
	}

	static int GetClientArmor(int client)
	{
		return ExecFunc(s_GetClientArmorFunc, client);
	}

	static int GetClientDeaths(int client)
	{
		return ExecFunc(s_GetClientDeathsFunc, client);
	}

	static int GetClientFrags(int client)
	{
		return ExecFunc(s_GetClientFragsFunc, client);
	}

	static int GetClientDataRate(int client)
	{
		return ExecFunc(s_GetClientDataRateFunc, client);
	}

	static bool IsClientTimingOut(int client)
	{
		return ExecFunc(s_IsClientTimingOutFunc, client);
	}

	static float GetClientTime(int client)
	{
		return sp_ctof(ExecFunc(s_GetClientTimeFunc, client));
	}

	static float GetClientLatency(int client, NetFlow flow)
	{
		return sp_ctof(ExecFunc(s_GetClientLatencyFunc, client, flow));
	}

	static float GetClientAvgLatency(int client, NetFlow flow)
	{
		return sp_ctof(ExecFunc(s_GetClientAvgLatencyFunc, client, flow));
	}

	static float GetClientAvgLoss(int client, NetFlow flow)
	{
		return sp_ctof(ExecFunc(s_GetClientAvgLossFunc, client, flow));
	}

	static float GetClientAvgChoke(int client, NetFlow flow)
	{
		return sp_ctof(ExecFunc(s_GetClientAvgChokeFunc, client, flow));
	}

	static float GetClientAvgData(int client, NetFlow flow)
	{
		return sp_ctof(ExecFunc(s_GetClientAvgDataFunc, client, flow));
	}

	static float GetClientAvgPackets(int client, NetFlow flow)
	{
		return sp_ctof(ExecFunc(s_GetClientAvgPacketsFunc, client, flow));
	}

	static int GetClientOfUserId(int userid)
	{
		return ExecFunc(s_GetClientOfUserIdFunc, userid);
	}

	static void KickClient(int client, const char* message)
	{
		ExecFunc(s_KickClientFunc, client, message);
	}

	static void KickClientEx(int client, const char* message)
	{
		ExecFunc(s_KickClientExFunc, client, message);
	}

	static void ChangeClientTeam(int client, int team)
	{
		ExecFunc(s_ChangeClientTeamFunc, client, team);
	}

	static int GetClientSerial(int client)
	{
		return ExecFunc(s_GetClientSerialFunc, client);
	}

	static int GetClientFromSerial(int serial)
	{
		return ExecFunc(s_GetClientFromSerialFunc, serial);
	}
