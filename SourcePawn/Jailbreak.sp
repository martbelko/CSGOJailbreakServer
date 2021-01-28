native int native_OnRoundStartPre();
native int native_OnRoundStartPost();
native int native_CMDCallback(int client, char[] command, char[] args);
native int native_OnPluginStart();
native int native_OnPluginEnd();
native int native_OnMapStart();
native int native_OnMapEnd();
// Client.inc - Natives declaration
native int native_OnClientConnect(int client, char[] rejectmsg, int maxlen);
native int native_OnClientConnected(int client);
native int native_OnClientPutInServer(int client);
native int native_OnClientDisconnect(int client);
native int native_OnClientDisconnect_Post(int client);
native int native_OnClientCommand(int client, int args);
native int native_OnClientCommandKeyValues(int client, KeyValues kv);
native int native_OnClientCommandKeyValues_Post(int client, KeyValues kv);
native int native_OnClientSettingsChanged(int client);
native int native_OnClientAuthorized(int client, const char[] auth);
native int native_OnClientPreAdminCheck(int client);
native int native_OnClientPostAdminFilter(int client);
native int native_OnClientPostAdminCheck(int client);

public void OnPluginStart()
{
	HookEvent("round_start", OnRoundStartPre, EventHookMode_Pre);
	HookEvent("round_start", OnRoundStartPost, EventHookMode_Post);
	
	native_OnPluginStart();
}

public Action CMDCallback(int client, int argc)
{
	char cmd[32];
	GetCmdArg(0, cmd, sizeof(cmd));
	char args[255];
	GetCmdArgString(args, sizeof(args));
	native_CMDCallback(client, cmd, args);
}

public void OnPluginEnd() { native_OnPluginEnd(); }

public void OnMapStart() { native_OnMapStart(); }
public void OnMapEnd() { native_OnMapEnd(); }

public Action OnRoundStartPre(Handle event, const char[] name, bool dontBroadcast)  { native_OnRoundStartPre(); }
public Action OnRoundStartPost(Handle event, const char[] name, bool dontBroadcast) { native_OnRoundStartPost(); }

public void public_PrintToChat(int client, const char[] message) { PrintToChat(client, message); }
public void public_PrintToConsole(int client, const char[] message) { PrintToConsole(client, message); }

public void public_RegConsoleCmd(const char[] command, const char[] description, int flags) { RegConsoleCmd(command, CMDCallback, description, flags); }


/* Client.inc */
// Client.inc - Natives
public bool OnClientConnect(int client, char[] rejectmsg, int maxlen) { return view_as<bool>(native_OnClientConnect(client, rejectmsg, maxlen)); }
public void OnClientConnected(int client) { native_OnClientConnected(client); }
public void OnClientPutInServer(int client) { native_OnClientPutInServer(client); }
public void OnClientDisconnect(int client) { native_OnClientDisconnect(client); }
public void OnClientDisconnect_Post(int client) { native_OnClientDisconnect_Post(client); }
public Action OnClientCommand(int client, int args) { return view_as<Action>(native_OnClientCommand(client, args)); }
public Action OnClientCommandKeyValues(int client, KeyValues kv) { return view_as<Action>(native_OnClientCommandKeyValues(client, kv)); }
public void OnClientCommandKeyValues_Post(int client, KeyValues kv) { native_OnClientCommandKeyValues_Post(client, kv); }
public void OnClientSettingsChanged(int client) { native_OnClientSettingsChanged(client); }
public void OnClientAuthorized(int client, const char[] auth) { native_OnClientAuthorized(client, auth); }
public Action OnClientPreAdminCheck(int client) { return view_as<Action>(native_OnClientPreAdminCheck(client)); }
public void OnClientPostAdminFilter(int client) { native_OnClientPostAdminFilter(client); }
public void OnClientPostAdminCheck(int client) { native_OnClientPostAdminCheck(client); }
// Client.inc - Public
public int public_GetMaxClients() { return MaxClients; }
public int public_GetMaxHumanPlayers() { return GetMaxHumanPlayers(); }
public int public_GetClientCount(bool inGameOnly) { return GetClientCount(inGameOnly); }
public bool public_GetClientName(int client, char[] name, int maxlen) { return GetClientName(client, name, maxlen); }
public bool public_GetClientIP(int client, char[] ip, int maxlen, bool remport) { return GetClientIP(client, ip, maxlen, remport); }
public bool public_GetClientAuthId(int client, AuthIdType authType, char[] auth, int maxlen, bool validate) { return GetClientAuthId(client, authType, auth, maxlen, validate); }
public int public_GetSteamAccountID(int client, bool validate) { return GetSteamAccountID(client, validate); }
public int public_GetClientUserId(int client) { return GetClientUserId(client); }
public bool public_IsClientConnected(int client) { return IsClientConnected(client); }
public bool public_IsClientInGame(int client) { return IsClientInGame(client); }
public bool public_IsClientInKickQueue(int client) { return IsClientInKickQueue(client); }
public bool public_IsClientAuthorized(int client) { return IsClientAuthorized(client); }
public bool public_IsFakeClient(int client) { return IsFakeClient(client); }
public bool public_IsClientSourceTV(int client) { return IsClientSourceTV(client); }
public bool public_IsClientReplay(int client) { return IsClientReplay(client); }
public bool public_IsClientObserver(int client) { return IsClientObserver(client); }
public bool public_IsPlayerAlive(int client) { return IsPlayerAlive(client); }
public bool public_GetClientInfo(int client, const char[] key, char[] value, int maxlen) { return GetClientInfo(client, key, value, maxlen); }
public int public_GetClientTeam(int client) { return GetClientTeam(client); }
public void public_SetUserAdmin(int client, AdminId id, bool temp) { SetUserAdmin(client, id, temp); }
public AdminId public_GetUserAdmin(int client) { return GetUserAdmin(client); }
public void public_AddUserFlags(int client, AdminFlag flag) { AddUserFlags(client, flag); } // TODO: AdminFlag ... flags
public void public_RemoveUserFlags(int client, AdminFlag flag) { RemoveUserFlags(client, flag); } // TODO: AdminFlag ... flags
public void public_SetUserFlagBits(int client, int flags) { SetUserFlagBits(client, flags); }
public int public_GetUserFlagBits(int client) { return GetUserFlagBits(client); }
public bool public_CanUserTarget(int client, int target) { return CanUserTarget(client, target); }
public bool public_RunAdminCacheChecks(int client) { return RunAdminCacheChecks(client); }
public void public_NotifyPostAdminCheck(int client) { NotifyPostAdminCheck(client); }
public int public_CreateFakeClient(const char[] name) { return CreateFakeClient(name); }
public void public_SetFakeClientConVar(int client, const char[] cvar, const char[] value) { SetFakeClientConVar(client, cvar, value); }
public int public_GetClientHealth(int client) { return GetClientHealth(client); }
public void public_GetClientModel(int client, char[] model, int maxlen) { GetClientModel(client, model, maxlen); }
public void public_GetClientWeapon(int client, char[] weapon, int maxlen) { GetClientWeapon(client, weapon, maxlen); }
public void public_GetClientMaxs(int client, float vec[3]) { GetClientMaxs(client, vec); }
public void public_GetClientMins(int client, float vec[3]) { GetClientMins(client, vec); }
public void public_GetClientAbsAngles(int client, float ang[3]) { GetClientAbsAngles(client, ang); }
public void public_GetClientAbsOrigin(int client, float vec[3]) { GetClientAbsOrigin(client, vec); }
public int public_GetClientArmor(int client) { return GetClientArmor(client); }
public int public_GetClientDeaths(int client) { return GetClientDeaths(client); }
public int public_GetClientFrags(int client) { return GetClientFrags(client); }
public int public_GetClientDataRate(int client) { return GetClientDataRate(client); }
public bool public_IsClientTimingOut(int client) { return IsClientTimingOut(client); }
public float public_GetClientTime(int client) { return GetClientTime(client); }
public float public_GetClientLatency(int client, NetFlow flow) { return GetClientLatency(client, flow); }
public float public_GetClientAvgLatency(int client, NetFlow flow) { return GetClientAvgLatency(client, flow); }
public float public_GetClientAvgLoss(int client, NetFlow flow) { return GetClientAvgLoss(client, flow); }
public float public_GetClientAvgChoke(int client, NetFlow flow) { return GetClientAvgChoke(client, flow); }
public float public_GetClientAvgData(int client, NetFlow flow) { return GetClientAvgData(client, flow); }
public float public_GetClientAvgPackets(int client, NetFlow flow) { return GetClientAvgPackets(client, flow); }
public int public_GetClientOfUserId(int userid) { return GetClientOfUserId(userid); }
public void public_KickClient(int client, const char[] message) { KickClient(client, message); }
public void public_KickClientEx(int client, const char[] message) { KickClientEx(client, message); }
public void public_ChangeClientTeam(int client, int team) { ChangeClientTeam(client, team); }
public int public_GetClientSerial(int client) { return GetClientSerial(client); }
public int public_GetClientFromSerial(int serial) { return GetClientFromSerial(serial); }
