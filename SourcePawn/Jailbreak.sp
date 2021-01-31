#include <cstrike>

// Native Callbacks
native Action native_ConCmdCallback(int client, char[] command, char[] args);
native Action native_SrvCmdCallback(char[] command, char[] args);
native Action native_CmdListenerCallback(int client, const char[] command, int argc);
native void native_SQLTxnSuccessCallback(Database db, int data, int numQueries, DBResultSet[] results, int[] queryData);
native void native_SQLTxnFailureCallback(Database db, int data, int numQueries, const char[] error, int failIndex, int[] queryData);
native void native_SQLTCallbackConnect(Handle owner, Handle hndl, const char[] error, int data);
native void native_SQLTCallbackQuery(Handle owner, Handle hndl, const char[] error, int data);
native Action native_EventHookCallbackPre(Event event, const char[] name, bool dontBroadcast);
native Action native_EventHookCallbackPost(Event event, const char[] name, bool dontBroadcast);
native Action native_EventHookCallbackPostNoCopy(Event event, const char[] name, bool dontBroadcast);

// Not known for now
native int native_OnPluginStart();
native int native_OnPluginEnd();
native int native_OnMapStart();
native int native_OnMapEnd();

// cstrike.inc - Natives declaration
native Action native_CS_OnBuyCommand(int client, const char[] weapon);
native Action native_CS_OnCSWeaponDrop(int client, int weaponIndex);
native Action native_CS_OnGetWeaponPrice(int client, const char[] weapon, int &price);
native Action native_CS_OnTerminateRound(float &delay, CSRoundEndReason &reason);

// Console.inc - Natives declaration
native Action native_OnClientSayCommand(int client, const char[] command, const char[] sArgs);
native int native_OnClientSayCommand_Post(int client, const char[] command, const char[] sArgs);

// Client.inc - Natives declaration
native bool native_OnClientConnect(int client, char[] rejectmsg, int maxlen);
native int native_OnClientConnected(int client);
native int native_OnClientPutInServer(int client);
native int native_OnClientDisconnect(int client);
native int native_OnClientDisconnect_Post(int client);
native Action native_OnClientCommand(int client, int args);
native Action native_OnClientCommandKeyValues(int client, KeyValues kv);
native int native_OnClientCommandKeyValues_Post(int client, KeyValues kv);
native int native_OnClientSettingsChanged(int client);
native int native_OnClientAuthorized(int client, const char[] auth);
native Action native_OnClientPreAdminCheck(int client);
native int native_OnClientPostAdminFilter(int client);
native int native_OnClientPostAdminCheck(int client);


// TODO
public void OnPluginStart()
{
	native_OnPluginStart();
}




// Callbacks
public Action ConCmdCallback(int client, int argc)
{
	char cmd[32];
	GetCmdArg(0, cmd, sizeof(cmd));
	char args[255];
	GetCmdArgString(args, sizeof(args));
	native_ConCmdCallback(client, cmd, args);
}
public Action SrvCmdCallback(int argc)
{
	char cmd[32];
	GetCmdArg(0, cmd, sizeof(cmd));
	char args[255];
	GetCmdArgString(args, sizeof(args));
	native_SrvCmdCallback(cmd, args);
}
public Action CmdListenerCallback(int client, const char[] command, int argc) { return native_CmdListenerCallback(client, command, argc); }
public void SQLTxnSuccessCallback(Database db, any data, int numQueries, DBResultSet[] results, any[] queryData) { native_SQLTxnSuccessCallback(db, data, numQueries, results, queryData); }
public void SQLTxnFailureCallback(Database db, any data, int numQueries, const char[] error, int failIndex, any[] queryData) { native_SQLTxnFailureCallback(db, data, numQueries, error, failIndex, queryData); }
public void SQLTCallbackConnectFunc(Handle owner, Handle hndl, const char[] error, int data) { native_SQLTCallbackConnect(owner, hndl, error, data); }
public void SQLTCallbackQueryFunc(Handle owner, Handle hndl, const char[] error, int data) { native_SQLTCallbackQuery(owner, hndl, error, data); }
public Action EventHookCallbackPre(Event event, const char[] name, bool dontBroadcast) { return native_EventHookCallbackPre(event, name, dontBroadcast); }
public Action EventHookCallbackPost(Event event, const char[] name, bool dontBroadcast) { return native_EventHookCallbackPost(event, name, dontBroadcast); }
public Action EventHookCallbackPostNoCopy(Event event, const char[] name, bool dontBroadcast) { return native_EventHookCallbackPostNoCopy(event, name, dontBroadcast); }

// TODO
public void OnPluginEnd() { native_OnPluginEnd(); }

public void OnMapStart() { native_OnMapStart(); }
public void OnMapEnd() { native_OnMapEnd(); }

// EVENTS.INC
public void public_HookEvent(const char[] name, EventHookMode mode)
{
	if (mode == EventHookMode_Pre) { HookEvent(name, EventHookCallbackPre, EventHookMode_Pre); }
	else if (mode == EventHookMode_PostNoCopy) { HookEvent(name, EventHookCallbackPostNoCopy, EventHookMode_PostNoCopy); }
	else { HookEvent(name, EventHookCallbackPost, EventHookMode_Post); }
}
public bool public_HookEventEx(const char[] name, EventHookMode mode)
{
	if (mode == EventHookMode_Pre) { return HookEventEx(name, EventHookCallbackPre, EventHookMode_Pre); }
	else if (mode == EventHookMode_PostNoCopy) { return HookEventEx(name, EventHookCallbackPost, EventHookMode_PostNoCopy); }
	return HookEventEx(name, EventHookCallbackPostNoCopy, EventHookMode_Post);
}
public void public_UnhookEvent(const char[] name, EventHookMode mode)
{
	if (mode == EventHookMode_Pre) { UnhookEvent(name, EventHookCallbackPre, EventHookMode_Pre); }
	else if (mode == EventHookMode_Post) { UnhookEvent(name, EventHookCallbackPostNoCopy, EventHookMode_Post); }
	else { UnhookEvent(name, EventHookCallbackPost, EventHookMode_PostNoCopy); }
}
public Event public_CreateEvent(const char[] name, bool force) { return CreateEvent(name, force); }
public void public_FireEvent(Handle event, bool dontBroadcast) { FireEvent(event, dontBroadcast); }
public void public_CancelCreatedEvent(Handle event) { CancelCreatedEvent(event); }
public bool public_GetEventBool(Handle event, const char[] key, bool defValue) { return GetEventBool(event, key, defValue); }
public void public_SetEventBool(Handle event, const char[] key, bool value) { SetEventBool(event, key, value); }
public int public_GetEventInt(Handle event, const char[] key, int defValue) { return GetEventInt(event, key, defValue); }
public void public_SetEventInt(Handle event, const char[] key, int value) { SetEventInt(event, key, value); }
public float public_GetEventFloat(Handle event, const char[] key, float defValue) { return GetEventFloat(event, key, defValue); }
public void public_SetEventFloat(Handle event, const char[] key, float value) { SetEventFloat(event, key, value); }
public void public_GetEventString(Handle event, const char[] key, char[] value, int maxlength, const char[] defvalue) { GetEventString(event, key, value, maxlength, defvalue); }
public void public_SetEventString(Handle event, const char[] key, const char[] value) { SetEventString(event, key, value); }
public void public_GetEventName(Handle event, char[] name, int maxlength) { GetEventName(event, name, maxlength); }
public void public_SetEventBroadcast(Handle event, bool dontBroadcast) { SetEventBroadcast(event, dontBroadcast); }

/* DBI.INC */
// DBI.INC - Public
public Database public_SQL_Connect(const char[] confname, bool persistent, char[] error, int maxlength) { return SQL_Connect(confname, persistent, error, maxlength); }
public Database public_SQL_ConnectCustom(Handle keyvalues, char[] error, int maxlength, bool persistent) { return SQL_ConnectCustom(keyvalues, error, maxlength, persistent); }
public bool public_SQL_CheckConfig(const char[] name) { return SQL_CheckConfig(name); }
public DBDriver public_SQL_GetDriver(const char[] name) { return SQL_GetDriver(name); }
public DBDriver public_SQL_ReadDriver(Handle database, char[] ident, int ident_length) { return SQL_ReadDriver(database, ident, ident_length); }
public void public_SQL_GetDriverIdent(Handle driver, char[] ident, int maxlength) { SQL_GetDriverIdent(driver, ident, maxlength); }
public void public_SQL_GetDriverProduct(Handle driver, char[] product, int maxlength) { SQL_GetDriverProduct(driver, product, maxlength); }
public bool public_SQL_SetCharset(Handle database, const char[] charset) { return SQL_SetCharset(database, charset); }
public int public_SQL_GetAffectedRows(Handle hndl) { return SQL_GetAffectedRows(hndl); }
public int public_SQL_GetInsertId(Handle hndl) { return SQL_GetInsertId(hndl); }
public bool public_SQL_GetError(Handle hndl, char[] error, int maxlength) { return SQL_GetError(hndl, error, maxlength); }
public bool public_SQL_EscapeString(Handle database, const char[] string, char[] buffer, int maxlength, int &written) { return SQL_EscapeString(database, string, buffer, maxlength, written); }
public int public_SQL_FormatQuery(Handle database, const char[] buffer, int maxlength, const char[] format, any...)
	{ char formatted[512]; VFormat(formatted, sizeof(formatted), format, 5); return SQL_FormatQuery(database, buffer, maxlength, formatted); }
public bool public_SQL_FastQuery(Handle database, const char[] query, int len) { return SQL_FastQuery(database, query, len); }
public DBResultSet public_SQL_Query(Handle database, const char[] query, int len) { return SQL_Query(database, query, len); }
public DBStatement public_SQL_PrepareQuery(Handle database, const char[] query, char[] error, int maxlength) { return SQL_PrepareQuery(database, query, error, maxlength); }
public bool public_SQL_FetchMoreResults(Handle query) { return SQL_FetchMoreResults(query); }
public bool public_SQL_HasResultSet(Handle query) { return SQL_HasResultSet(query); }
public int public_SQL_GetRowCount(Handle query) { return SQL_GetRowCount(query); }
public int public_SQL_GetFieldCount(Handle query) { return SQL_GetFieldCount(query); }
public void public_SQL_FieldNumToName(Handle query, int field, char[] name, int maxlength) { SQL_FieldNumToName(query, field, name, maxlength); }
public bool public_SQL_FieldNameToNum(Handle query, const char[] name, int &field) { return SQL_FieldNameToNum(query, name, field); }
public bool public_SQL_FetchRow(Handle query) { return SQL_FetchRow(query); }
public bool public_SQL_MoreRows(Handle query) { return SQL_MoreRows(query); }
public bool public_SQL_Rewind(Handle query) { return SQL_Rewind(query); }
public int public_SQL_FetchString(Handle query, int field, char[] buffer, int maxlength, DBResult &result) { return SQL_FetchString(query, field, buffer, maxlength, result); }
public float public_SQL_FetchFloat(Handle query, int field, DBResult &result) { return SQL_FetchFloat(query, field, result); }
public int public_SQL_FetchInt(Handle query, int field, DBResult &result) { return SQL_FetchInt(query, field, result); }
public bool public_SQL_IsFieldNull(Handle query, int field) { return SQL_IsFieldNull(query, field); }
public int public_SQL_FetchSize(Handle query, int field) { return SQL_FetchSize(query, field); }
public void public_SQL_BindParamInt(Handle statement, int param, int number, bool signed) { SQL_BindParamInt(statement, param, number, signed); }
public void public_SQL_BindParamFloat(Handle statement, int param, float value) { SQL_BindParamFloat(statement, param, value); }
public void public_SQL_BindParamString(Handle statement, int param, const char[] value, bool copy) { SQL_BindParamString(statement, param, value, copy); }
public bool public_SQL_Execute(Handle statement) { return SQL_Execute(statement); }
public void public_SQL_LockDatabase(Handle database) { SQL_LockDatabase(database); }
public void public_SQL_UnlockDatabase(Handle database) { SQL_UnlockDatabase(database); }
public bool public_SQL_IsSameConnection(Handle hndl1, Handle hndl2) { return SQL_IsSameConnection(hndl1, hndl2); }
public void public_SQL_TConnect(const char[] name, int data) { SQL_TConnect(SQLTCallbackConnectFunc, name, data); }
public void public_SQL_TQuery(Handle database, const char[] query, int data, DBPriority prio) { SQL_TQuery(database, SQLTCallbackQueryFunc, query, data, prio); }
public Transaction public_SQL_CreateTransaction() { return SQL_CreateTransaction(); }
public int public_SQL_AddQuery(Transaction txn, const char[] query, int data) { return SQL_AddQuery(txn, query, data); }
public void public_SQL_ExecuteTransaction(Handle db, Transaction txn, int data, DBPriority priority)
	{ SQL_ExecuteTransaction(db, txn, SQLTxnSuccessCallback, SQLTxnFailureCallback, data, priority); }

/*stock Database SQL_DefConnect(char[] error, int maxlength, bool persistent=true)
{
	return SQL_Connect("default", persistent, error, maxlength);
}*/

/* CSTRIKE.INC */
// cstrike.inc - Natives
public Action CS_OnBuyCommand(int client, const char[] weapon) { return native_CS_OnBuyCommand(client, weapon); }
public Action CS_OnCSWeaponDrop(int client, int weaponIndex) { return native_CS_OnCSWeaponDrop(client, weaponIndex); }
public Action CS_OnGetWeaponPrice(int client, const char[] weapon, int &price) { return native_CS_OnGetWeaponPrice(client, weapon, price); }
public Action CS_OnTerminateRound(float &delay, CSRoundEndReason &reason) { return native_CS_OnTerminateRound(delay, reason); }
// cstrike.inc - Public
public void public_CS_RespawnPlayer(int client) { CS_RespawnPlayer(client); }
public void public_CS_SwitchTeam(int client, int team) { CS_SwitchTeam(client, team); }
public void public_CS_DropWeapon(int client, int weaponIndex, bool toss, bool blockhook) { CS_DropWeapon(client, weaponIndex, toss, blockhook); }
public void public_CS_TerminateRound(float delay, CSRoundEndReason reason, bool blockhook) { CS_TerminateRound(delay, reason, blockhook); }
public void public_CS_GetTranslatedWeaponAlias(const char[] alias, char[] weapon, int size) { CS_GetTranslatedWeaponAlias(alias, weapon, size); }
public int public_CS_GetWeaponPrice(int client, CSWeaponID id, bool defaultprice) { return CS_GetWeaponPrice(client, id, defaultprice); }
public int public_CS_GetClientClanTag(int client, char[] buffer, int size) { return CS_GetClientClanTag(client, buffer, size); }
public void public_CS_SetClientClanTag(int client, const char[] tag) { CS_SetClientClanTag(client, tag); }
public int public_CS_GetTeamScore(int team) { return CS_GetTeamScore(team); }
public void public_CS_SetTeamScore(int team, int value) { CS_SetTeamScore(team, value); }
public int public_CS_GetMVPCount(int client) { return CS_GetMVPCount(client); }
public void public_CS_SetMVPCount(int client, int value) { CS_SetMVPCount(client, value); }
public int public_CS_GetClientContributionScore(int client) { return CS_GetClientContributionScore(client); }
public void public_CS_SetClientContributionScore(int client, int value) { CS_SetClientContributionScore(client, value); }
public int public_CS_GetClientAssists(int client) { return CS_GetClientAssists(client); }
public void public_CS_SetClientAssists(int client, int value) { CS_SetClientAssists(client, value); }
public CSWeaponID public_CS_AliasToWeaponID(const char[] alias) { return CS_AliasToWeaponID(alias); }
public int public_CS_WeaponIDToAlias(CSWeaponID weaponID, char[] destination, int len) { return CS_WeaponIDToAlias(weaponID, destination, len); }
public bool public_CS_IsValidWeaponID(CSWeaponID id) { return CS_IsValidWeaponID(id); }
public void public_CS_UpdateClientModel(int client) { CS_UpdateClientModel(client); }
public CSWeaponID public_CS_ItemDefIndexToID(int iDefIndex) { return CS_ItemDefIndexToID(iDefIndex); }
public int public_CS_WeaponIDToItemDefIndex(CSWeaponID id) { return CS_WeaponIDToItemDefIndex(id); }

/* CONSOLE.INC */
// Console.inc - Natives
public Action OnClientSayCommand(int client, const char[] command, const char[] sArgs) { return native_OnClientSayCommand(client, command, sArgs); }
public void OnClientSayCommand_Post(int client, const char[] command, const char[] sArgs) { native_OnClientSayCommand_Post(client, command, sArgs); }

// Console.inc - Public
public void public_ServerCommand(const char[] format, any ...) { char cmd[512]; VFormat(cmd, sizeof(cmd), format, 2); ServerCommand(cmd); }
public void public_ServerCommandEx(char[] buffer, int maxlen, const char[] format, any ...) { char cmd[512]; VFormat(cmd, sizeof(cmd), format, 4); ServerCommandEx(buffer, maxlen, cmd); }
public void public_InsertServerCommand(const char[] format, any ...) { char cmd[512]; VFormat(cmd, sizeof(cmd), format, 2); InsertServerCommand(cmd); }
public void public_ServerExecute() { ServerExecute(); }
public void public_ClientCommand(int client, const char[] fmt, any ...) { char cmd[512]; VFormat(cmd, sizeof(cmd), fmt, 3); ClientCommand(client, cmd); }
public void public_FakeClientCommand(int client, const char[] fmt, any ...) { char cmd[512]; VFormat(cmd, sizeof(cmd), fmt, 3); FakeClientCommand(client, cmd); }
public void public_FakeClientCommandEx(int client, const char[] fmt, any ...) { char cmd[512]; VFormat(cmd, sizeof(cmd), fmt, 3); FakeClientCommandEx(client, cmd); }
public void public_FakeClientCommandKeyValues(int client, KeyValues kv) { FakeClientCommandKeyValues(client, kv); }
public void public_PrintToServer(const char[] format, any ...) { char message[512]; VFormat(message, sizeof(message), format, 2); PrintToServer(message); }
public void public_PrintToConsole(int client, const char[] format, any ...) { char message[512]; VFormat(message, sizeof(message), format, 3); PrintToConsole(client, message); }
public void public_ReplyToCommand(int client, const char[] format, any ...) { char reply[512]; VFormat(reply, sizeof(reply), format, 3); ReplyToCommand(client, reply); }
public ReplySource public_GetCmdReplySource() { return GetCmdReplySource(); }
public ReplySource public_SetCmdReplySource(ReplySource source) { return SetCmdReplySource(source); }
public bool public_IsChatTrigger() { return IsChatTrigger(); }
public void public_ShowActivity2(int client, const char[] tag, const char[] format, any ...) { char activity[512]; VFormat(activity, sizeof(activity), format, 4); ShowActivity2(client, tag, activity); }
public void public_ShowActivity(int client, const char[] format, any ...) { char activity[512]; VFormat(activity, sizeof(activity), format, 3); ShowActivity(client, activity); }
public void public_ShowActivityEx(int client, const char[] tag, const char[] format, any ...) { char activity[512]; VFormat(activity, sizeof(activity), format, 4); ShowActivityEx(client, tag, activity); }
public bool public_FormatActivitySource(int client, int target, const char[] namebuf, int maxlength) { return FormatActivitySource(client, target, namebuf, maxlength); }
public void public_RegServerCmd(const char[] cmd, const char[] description, int flags) { RegServerCmd(cmd, SrvCmdCallback, description, flags); }
public void public_RegConsoleCmd(const char[] cmd, const char[] description, int flags) { RegConsoleCmd(cmd, ConCmdCallback, description, flags); }
public void public_RegAdminCmd(const char[] cmd, int adminflags, const char[] description, const char[] group, int flags) { RegAdminCmd(cmd, ConCmdCallback, adminflags, description, group, flags); }
public int public_GetCmdArgs() { return GetCmdArgs(); }
public int public_GetCmdArg(int argnum, char[] buffer, int maxlength) { return GetCmdArg(argnum, buffer, maxlength); }
public int public_GetCmdArgString(char[] buffer, int maxlength) { return GetCmdArgString(buffer, maxlength); }
public Handle public_GetCommandIterator() { return GetCommandIterator(); }
public bool public_ReadCommandIterator(Handle iter, char[] name, int nameLen, int &eflags, char[] desc, int descLen) { return ReadCommandIterator(iter, name, nameLen, eflags, desc, descLen); }
public bool public_CheckCommandAccess(int client, const char[] command, int flags, bool override_only) { return CheckCommandAccess(client, command, flags, override_only); }
public bool public_CheckAccess(AdminId id, const char[] command, int flags, bool override_only) { return CheckAccess(id, command, flags, override_only); }
public int public_GetCommandFlags(const char[] name) { return GetCommandFlags(name); }
public bool public_SetCommandFlags(const char[] name, int flags) { return SetCommandFlags(name, flags); }
public Handle public_FindFirstConCommand(char[] buffer, int max_size, bool &isCommand, int &flags, char[] description, int descrmax_size) { return FindFirstConCommand(buffer, max_size, isCommand, flags, description, descrmax_size); }
public bool public_FindNextConCommand(Handle search, char[] buffer, int max_size, bool &isCommand, int &flags, char[] description, int descrmax_size) { return FindNextConCommand(search, buffer, max_size, isCommand, flags, description, descrmax_size); }
public void public_AddServerTag(const char[] tag) { AddServerTag(tag); }
public void public_RemoveServerTag(const char[] tag) { RemoveServerTag(tag); }
public bool public_AddCommandListener(const char[] command) { return AddCommandListener(CmdListenerCallback, command); }
public void public_RemoveCommandListener(const char[] command) { RemoveCommandListener(CmdListenerCallback, command); }

/* Client.inc */
// Client.inc - Natives
public bool OnClientConnect(int client, char[] rejectmsg, int maxlen) { return native_OnClientConnect(client, rejectmsg, maxlen); }
public void OnClientConnected(int client) { native_OnClientConnected(client); }
public void OnClientPutInServer(int client) { native_OnClientPutInServer(client); }
public void OnClientDisconnect(int client) { native_OnClientDisconnect(client); }
public void OnClientDisconnect_Post(int client) { native_OnClientDisconnect_Post(client); }
public Action OnClientCommand(int client, int args) { return native_OnClientCommand(client, args); }
public Action OnClientCommandKeyValues(int client, KeyValues kv) { return native_OnClientCommandKeyValues(client, kv); }
public void OnClientCommandKeyValues_Post(int client, KeyValues kv) { native_OnClientCommandKeyValues_Post(client, kv); }
public void OnClientSettingsChanged(int client) { native_OnClientSettingsChanged(client); }
public void OnClientAuthorized(int client, const char[] auth) { native_OnClientAuthorized(client, auth); }
public Action OnClientPreAdminCheck(int client) { return native_OnClientPreAdminCheck(client); }
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

/*stock void PrintToConsoleAll(const char[] format, any ...)
{
	char buffer[254];
	
	for (int i = 1; i <= MaxClients; i++)
	{
		if (IsClientInGame(i))
		{
			SetGlobalTransTarget(i);
			VFormat(buffer, sizeof(buffer), format, 2);
			PrintToConsole(i, "%s", buffer);
		}
	}
}*/


/*stock int GetCmdArgInt(int argnum)
{
    char str[12];
    GetCmdArg(argnum, str, sizeof(str));

    return StringToInt(str);
}*/

/*stock bool GetCmdArgIntEx(int argnum, int &value)
{
    char str[12];
    int len = GetCmdArg(argnum, str, sizeof(str));

    return StringToIntEx(str, value) == len && len > 0;
}*/

/*stock bool CommandExists(const char[] command)
{
	return (GetCommandFlags(command) != INVALID_FCVAR_FLAGS);
}*/
