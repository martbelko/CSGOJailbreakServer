public:
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

	template<typename ... Args>
	static void AddUserFlags(int client, Args ... flags)
	{
		PushArg(s_AddUserFlagsFunc, client);
		AddUserFlagsSub(flags...);
	}
private:
	static void AddUserFlagsSub(AdminFlag flag)
	{
		PushArgRef(s_AddUserFlagsFunc, reinterpret_cast<int&>(flag));
		ExecAndReturn(s_AddUserFlagsFunc);
	}

	template<typename ... Args>
	static void AddUserFlagsSub(AdminFlag flag, Args ... flags)
	{
		PushArgRef(s_AddUserFlagsFunc, reinterpret_cast<int&>(flag));
		AddUserFlagsSub(flags...);
	}
public:
	template<typename ... Args>
	static void RemoveUserFlags(int client, Args ... flags)
	{
		RemoveUserFlags(s_RemoveUserFlagsFunc, client);
		RemoveUserFlagsSub(flags...);
	}
private:
	static void RemoveUserFlagsSub(AdminFlag flag)
	{
		PushArgRef(s_RemoveUserFlagsFunc, reinterpret_cast<int&>(flag));
		ExecAndReturn(s_RemoveUserFlagsFunc);
	}

	template<typename ... Args>
	static void RemoveUserFlagsSub(AdminFlag flag, Args ... flags)
	{
		PushArgRef(s_RemoveUserFlagsFunc, reinterpret_cast<int&>(flag));
		RemoveUserFlagsSub(flags...);
	}
public:
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
