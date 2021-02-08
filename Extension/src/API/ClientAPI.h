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
		PushArg(s_GetClientNameFunc, client);
		PushArg(s_GetClientNameFunc, name, maxlen);
		PushArg(s_GetClientNameFunc, maxlen);
		return ExecFunc(s_GetClientNameFunc);
	}

	static bool GetClientIP(int client, char* ip, int maxlen, bool remport)
	{
		PushArg(s_GetClientIPFunc, client);
		PushArg(s_GetClientIPFunc, ip, maxlen);
		PushArg(s_GetClientIPFunc, maxlen);
		PushArg(s_GetClientIPFunc, remport);
		return ExecFunc(s_GetClientIPFunc);
	}

	static bool GetClientAuthId(int client, AuthIdType authType, char* auth, int maxlen, bool validate)
	{
		PushArg(s_GetClientAuthIdFunc, client);
		PushArg(s_GetClientAuthIdFunc, authType);
		PushArg(s_GetClientAuthIdFunc, auth, maxlen);
		PushArg(s_GetClientAuthIdFunc, maxlen);
		PushArg(s_GetClientAuthIdFunc, validate);
		return ExecFunc(s_GetClientAuthIdFunc);
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
		PushArg(s_GetClientInfoFunc, client);
		PushArg(s_GetClientInfoFunc, key);
		PushArg(s_GetClientInfoFunc, value, maxlen);
		PushArg(s_GetClientInfoFunc, maxlen);
		return ExecFunc(s_GetClientInfoFunc);
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

	template<typename ... Args>
	static void AddUserFlags(int client, Args ... args)
	{
		PushArg(s_AddUserFlagsFunc, client);
		AddUserFlagsSub(args...);
	}
private:
	static void AddUserFlagsSub(AdminFlag flag)
	{
		ExecFunc(s_AddUserFlagsFunc, flag);
	}

	template<typename ... Args>
	static void AddUserFlagsSub(AdminFlag flag, Args ... args)
	{
		ExecFunc(s_AddUserFlagsFunc, flag);
		AddUserFlagsSub(args...);
	}
public:
	template<typename ... Args>
	static void RemoveUserFlags(int client, Args ... args)
	{
		PushArg(s_RemoveUserFlagsFunc, client);
		RemoveUserFlagsSub(args...);
	}
private:
	static void RemoveUserFlagsSub(AdminFlag flag)
	{
		ExecFunc(s_RemoveUserFlagsFunc, flag);
	}

	template<typename ... Args>
	static void RemoveUserFlagsSub(AdminFlag flag, Args ... args)
	{
		ExecFunc(s_RemoveUserFlagsFunc, flag);
		AddUserFlagsSub(args...);
	}
public:
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
		PushArg(s_GetClientModelFunc, model, maxlen);
		PushArg(s_GetClientModelFunc, maxlen);
		ExecFunc(s_GetClientModelFunc);
	}

	static void GetClientWeapon(int client, char* weapon, int maxlen)
	{
		PushArg(s_GetClientWeaponFunc, client);
		PushArg(s_GetClientWeaponFunc, weapon, maxlen);
		PushArg(s_GetClientWeaponFunc, maxlen);
		ExecFunc(s_GetClientWeaponFunc);
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
		PushArg(s_GetClientAbsAnglesFunc, client);
		PushArg(s_GetClientAbsAnglesFunc, ang, 3);
		ExecFunc(s_GetClientAbsAnglesFunc);
	}

	static void GetClientAbsOrigin(int client, float vec[3])
	{
		PushArg(s_GetClientAbsOriginFunc, client);
		PushArg(s_GetClientAbsOriginFunc, vec, 3);
		ExecFunc(s_GetClientAbsOriginFunc);
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
