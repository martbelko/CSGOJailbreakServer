#include <cstrike>
#include <sdkhooks>
#include <sdktools>

// SDKHooks helpers
static SDKHookCB s_SDKHookCallbacks[44];
// SDKHooks Native Callbacks
native void native_SDKHooksPreThink(int client);
native void native_SDKHooksPreThinkPost(int client);
native void native_SDKHooksPostThink(int client);
native void native_SDKHooksPostThinkPost(int client);
native void native_SDKHooksGroundEntChanged(int client);
native void native_SDKHooksSpawnPost(int entity);
native void native_SDKHooksThink(int entity);
native void native_SDKHooksThinkPost(int entity);
native void native_SDKHooksVPhysicsUpdate(int entity);
native void native_SDKHooksVPhysicsUpdatePost(int entity);
native Action native_SDKHooksSpawn(int entity);
native Action native_SDKHooksReload(int weapon);
native Action native_SDKHooksEndTouch(int entity, int other);
native Action native_SDKHooksStartTouch(int entity, int other);
native Action native_SDKHooksTouch(int entity, int other);
native Action native_SDKHooksBlocked(int entity, int other);
native Action native_SDKHooksSetTransmit(int entity, int client);
native Action native_SDKHooksWeaponCanSwitchTo(int client, int weapon);
native Action native_SDKHooksWeaponCanUse(int client, int weapon);
native Action native_SDKHooksWeaponDrop(int client, int weapon);
native Action native_SDKHooksWeaponEquip(int client, int weapon);
native Action native_SDKHooksWeaponSwitch(int client, int weapon);
native void native_SDKHooksEndTouchPost(int entity, int other);
native void native_SDKHooksStartTouchPost(int entity, int other);
native void native_SDKHooksTouchPost(int entity, int other);
native void native_SDKHooksBlockedPost(int entity, int other);
native void native_SDKHooksWeaponCanSwitchToPost(int client, int weapon);
native void native_SDKHooksWeaponCanUsePost(int client, int weapon);
native void native_SDKHooksWeaponDropPost(int client, int weapon);
native void native_SDKHooksWeaponEquipPost(int client, int weapon);
native void native_SDKHooksWeaponSwitchPost(int client, int weapon);
native Action native_SDKHooksGetMaxHealth(int entity, int& maxhealth);
native Action native_SDKHooksOnTakeDamage(int victim, int& attacker, int& inflictor, float& damage, int& damagetype, int& weapon, float damageForce[3], float damagePosition[3], int damagecustom);
native Action native_SDKHooksOnTakeDamageAlive(int victim, int& attacker, int& inflictor, float& damage, int& damagetype, int& weapon, float damageForce[3], float damagePosition[3], int damagecustom);
native void native_SDKHooksOnTakeDamagePost(int victim, int attacker, int inflictor, float damage, int damagetype, int weapon, const float damageForce[3], const float damagePosition[3], int damagecustom);
native void native_SDKHooksOnTakeDamageAlivePost(int victim, int attacker, int inflictor, float damage, int damagetype, int weapon, const float damageForce[3], const float damagePosition[3], int damagecustom);
native void native_SDKHooksFireBulletsPost(int client, int shots, const char[] weaponname);
native Action native_SDKHooksTraceAttack(int victim, int& attacker, int& inflictor, float& damage, int& damagetype, int& ammotype, int hitbox, int hitgroup);
native void native_SDKHooksTraceAttackPost(int victim, int attacker, int inflictor, float damage, int damagetype, int ammotype, int hitbox, int hitgroup);
native bool native_SDKHooksShouldCollide(int entity, int collisiongroup, int contentsmask, bool originalResult);
native Action native_SDKHooksUse(int entity, int activator, int caller, UseType type, float value);
native void native_SDKHooksUsePost(int entity, int activator, int caller, UseType type, float value);
native void native_SDKHooksReloadPost(int weapon, bool bSuccessful);
native bool native_SDKHooksCanBeAutobalanced(int client, bool origRet);

// Native Callbacks
native void native_SQLTxnSuccessCallback(Database db, int data, int numQueries, DBResultSet[] results, int[] queryData);
native void native_SQLTxnFailureCallback(Database db, int data, int numQueries, const char[] error, int failIndex, int[] queryData);
native void native_SQLTCallbackConnect(Handle owner, Handle hndl, const char[] error, int data);
native void native_SQLTCallbackQuery(Handle owner, Handle hndl, const char[] error, int data);
native Action native_EventHookCallbackPre(Event event, const char[] name, bool dontBroadcast);
native Action native_EventHookCallbackPost(Event event, const char[] name, bool dontBroadcast);
native Action native_EventHookCallbackPostNoCopy(Event event, const char[] name, bool dontBroadcast);
native int native_MenuHandlerCallback(Menu menu, MenuAction action, int param1, int param2);
native void native_VoteHandlerCallback(Menu menu, int num_votes, int num_clients, const int[][] client_info, int num_items, const int[][] item_info);

// SOURCEMOD.INC - Natives declaration
native int native_OnPluginStart();
native void native_OnPluginEnd();
native void native_OnPluginPauseChange(bool pause);
native void native_OnGameFrame();
native void native_OnMapStart();
native void native_OnMapEnd();
native void native_OnConfigsExecuted();
native void native_OnAutoConfigsBuffered();
native void native_OnAllPluginsLoaded();
native void native_OnLibraryAdded(const char[] name);
native void native_OnLibraryRemoved(const char[] name);
native bool native_OnClientFloodCheck(int client);
native void native_OnClientFloodResult(int client, bool blocked);

// SDKTOOLS_SOUND.INC - Natives declaration
native Action native_AmbientSHookCallback(char sample[PLATFORM_MAX_PATH], int &entity, float &volume, int &level, int &pitch,
	float pos[3], int &flags, float &delay);

native Action native_NormalSHookCallback(int clients[MAXPLAYERS], int &numClients, char sample[PLATFORM_MAX_PATH], int &entity,
	int &channel, float &volume, int &level, int &pitch, int &flags, char soundEntry[PLATFORM_MAX_PATH], int &seed);

// COMMANDFILTERS.INC - Natives declaration
native bool native_MultiTargetFilterCallback(const char[] pattern, Handle clients);

// SDKTOOLS_VOICE.INC - Natives declaration
native void native_OnClientSpeaking(int client);
native void native_OnClientSpeakingEnd(int client);

// SDKTOOLS_TRACE.INC - Natives declaration
native bool native_TraceEntityFilterCallback(int entity, int contentsMask, int data);
native bool native_TraceEntityEnumeratorCallback(int entity, int data);

// LOGGING.INC - Natives declaration
native Action native_OnLogAction(Handle source, Identity ident, int client, int target, const char[] message);
native Action native_GameLogHookCallback(const char[] message);

// SDKTOOLS_TEMPENTS.INC - Natives declaration
native Action native_TEHookCallback(const char[] te_name, const int[] Players, int numClients, float delay);

// SDKTOOLS_ENTOUTPUT.INC - Natives declaration
native Action native_EntityOutputCallback(const char[] output, int caller, int activator, float delay);
native Action native_SingleEntityOutputCallback(const char[] output, int caller, int activator, float delay);

// TIMERS.INC - Natives declaration
native Action native_TimerCallback(Handle timer, int data);
native void native_OnMapTimeLeftChanged();

// SDKTOOLS_HOOKS.INC - Natives declaration
native Action native_OnPlayerRunCmd(int client, int &buttons, int &impulse, float vel[3], float angles[3], int &weapon, int &subtype, int &cmdnum, int &tickcount, int &seed, int mouse[2]);
native void native_OnPlayerRunCmdPost(int client, int buttons, int impulse, const float vel[3], const float angles[3], int weapon, int subtype, int cmdnum, int tickcount, int seed, const int mouse[2]);
native Action native_OnFileSend(int client, const char[] sFile);
native Action native_OnFileReceive(int client, const char[] sFile);

// SDKHOOKS.INC - Natives declaration
native void native_OnEntityCreated(int entity, const char[] classname);
native void native_OnEntitySpawned(int entity, const char[] classname);
native void native_OnEntityDestroyed(int entity);
native Action native_OnGetGameDescription(char gameDesc[64]);
native Action native_OnLevelInit(const char[] mapName, char mapEntities[2097152]);

// CSTRIKE.INC - Natives declaration
native Action native_CS_OnBuyCommand(int client, const char[] weapon);
native Action native_CS_OnCSWeaponDrop(int client, int weaponIndex);
native Action native_CS_OnGetWeaponPrice(int client, const char[] weapon, int &price);
native Action native_CS_OnTerminateRound(float &delay, CSRoundEndReason &reason);

// CONSOLE.INC - Natives declaration
native Action native_OnClientSayCommand(int client, const char[] command, const char[] sArgs);
native int native_OnClientSayCommand_Post(int client, const char[] command, const char[] sArgs);

native Action native_ConCmdCallback(int client, int argc);
native Action native_SrvCmdCallback(int argc);
native Action native_CmdListenerCallback(int client, const char[] command, int argc);

// CLIENTS.INC - Natives declaration
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

// SDKHooks Callbacks
public void SDKHooksPreThink(int client)
	{ native_SDKHooksPreThink(client); }
public void SDKHooksPreThinkPost(int client)
	{ native_SDKHooksPreThinkPost(client); }
public void SDKHooksPostThink(int client)
	{ native_SDKHooksPostThink(client); }
public void SDKHooksPostThinkPost(int client)
	{ native_SDKHooksPostThinkPost(client); }
public void SDKHooksGroundEntChanged(int client)
	{ native_SDKHooksGroundEntChanged(client); }
public void SDKHooksSpawnPost(int entity)
	{ native_SDKHooksSpawnPost(entity); }
public void SDKHooksThink(int entity)
	{ native_SDKHooksThink(entity); }
public void SDKHooksThinkPost(int entity)
	{ native_SDKHooksThinkPost(entity); }
public void SDKHooksVPhysicsUpdate(int entity)
	{ native_SDKHooksVPhysicsUpdate(entity); }
public void SDKHooksVPhysicsUpdatePost(int entity)
	{ native_SDKHooksVPhysicsUpdatePost(entity); }
public Action SDKHooksSpawn(int entity)
	{ return native_SDKHooksSpawn(entity); }
public Action SDKHooksReload(int weapon)
	{ return native_SDKHooksReload(weapon); }
public Action SDKHooksEndTouch(int entity, int other)
	{ return native_SDKHooksEndTouch(entity, other); }
public Action SDKHooksStartTouch(int entity, int other)
	{ return native_SDKHooksStartTouch(entity, other); }
public Action SDKHooksTouch(int entity, int other)
	{ return native_SDKHooksTouch(entity, other); }
public Action SDKHooksBlocked(int entity, int other)
	{ return native_SDKHooksBlocked(entity, other); }
public Action SDKHooksSetTransmit(int entity, int client)
	{ return native_SDKHooksSetTransmit(entity, client); }
public Action SDKHooksWeaponCanSwitchTo(int client, int weapon)
	{ return native_SDKHooksWeaponCanSwitchTo(client, weapon); }
public Action SDKHooksWeaponCanUse(int client, int weapon)
	{ return native_SDKHooksWeaponCanUse(client, weapon); }
public Action SDKHooksWeaponDrop(int client, int weapon)
	{ return native_SDKHooksWeaponDrop(client, weapon); }
public Action SDKHooksWeaponEquip(int client, int weapon)
	{ return native_SDKHooksWeaponEquip(client, weapon); }
public Action SDKHooksWeaponSwitch(int client, int weapon)
	{ return native_SDKHooksWeaponSwitch(client, weapon); }
public void SDKHooksEndTouchPost(int entity, int other)
	{ native_SDKHooksEndTouchPost(entity, other); }
public void SDKHooksStartTouchPost(int entity, int other)
	{ native_SDKHooksStartTouchPost(entity, other); }
public void SDKHooksTouchPost(int entity, int other)
	{ native_SDKHooksTouchPost(entity, other); }
public void SDKHooksBlockedPost(int entity, int other)
	{ native_SDKHooksBlockedPost(entity, other); }
public void SDKHooksWeaponCanSwitchToPost(int client, int weapon)
	{ native_SDKHooksWeaponCanSwitchToPost(client, weapon); }
public void SDKHooksWeaponCanUsePost(int client, int weapon)
	{ native_SDKHooksWeaponCanUsePost(client, weapon); }
public void SDKHooksWeaponDropPost(int client, int weapon)
	{ native_SDKHooksWeaponDropPost(client, weapon); }
public void SDKHooksWeaponEquipPost(int client, int weapon)
	{ native_SDKHooksWeaponEquipPost(client, weapon); }
public void SDKHooksWeaponSwitchPost(int client, int weapon)
	{ native_SDKHooksWeaponSwitchPost(client, weapon); }
public Action SDKHooksGetMaxHealth(int entity, int& maxhealth)
	{ return native_SDKHooksGetMaxHealth(entity, maxhealth); }
public Action SDKHooksOnTakeDamage(int victim, int& attacker, int& inflictor, float& damage, int& damagetype, int& weapon, float damageForce[3], float damagePosition[3], int damagecustom)
	{ return native_SDKHooksOnTakeDamage(victim, attacker, inflictor, damage, damagetype, weapon, damageForce, damagePosition, damagecustom); }
public Action SDKHooksOnTakeDamageAlive(int victim, int& attacker, int& inflictor, float& damage, int& damagetype, int& weapon, float damageForce[3], float damagePosition[3], int damagecustom)
	{ return native_SDKHooksOnTakeDamageAlive(victim, attacker, inflictor, damage, damagetype, weapon, damageForce, damagePosition, damagecustom); }
public void SDKHooksOnTakeDamagePost(int victim, int attacker, int inflictor, float damage, int damagetype, int weapon, const float damageForce[3], const float damagePosition[3], int damagecustom)
	{ native_SDKHooksOnTakeDamagePost(victim, attacker, inflictor, damage, damagetype, weapon, damageForce, damagePosition, damagecustom); }
public void SDKHooksOnTakeDamageAlivePost(int victim, int attacker, int inflictor, float damage, int damagetype, int weapon, const float damageForce[3], const float damagePosition[3], int damagecustom)
	{ native_SDKHooksOnTakeDamageAlivePost(victim, attacker, inflictor, damage, damagetype, weapon, damageForce, damagePosition, damagecustom); }
public void SDKHooksFireBulletsPost(int client, int shots, const char[] weaponname)
	{ native_SDKHooksFireBulletsPost(client, shots, weaponname); }
public Action SDKHooksTraceAttack(int victim, int& attacker, int& inflictor, float& damage, int& damagetype, int& ammotype, int hitbox, int hitgroup)
	{ return native_SDKHooksTraceAttack(victim, attacker, inflictor, damage, damagetype, ammotype, hitbox, hitgroup); }
public void SDKHooksTraceAttackPost(int victim, int attacker, int inflictor, float damage, int damagetype, int ammotype, int hitbox, int hitgroup)
	{ native_SDKHooksTraceAttackPost(victim, attacker, inflictor, damage, damagetype, ammotype, hitbox, hitgroup); }
public bool SDKHooksShouldCollide(int entity, int collisiongroup, int contentsmask, bool originalResult)
	{ return native_SDKHooksShouldCollide(entity, collisiongroup, contentsmask, originalResult); }
public Action SDKHooksUse(int entity, int activator, int caller, UseType type, float value)
	{ return native_SDKHooksUse(entity, activator, caller, type, value); }
public void SDKHooksUsePost(int entity, int activator, int caller, UseType type, float value)
	{ native_SDKHooksUsePost(entity, activator, caller, type, value); }
public void SDKHooksReloadPost(int weapon, bool bSuccessful)
	{ native_SDKHooksReloadPost(weapon, bSuccessful); }
public bool SDKHooksCanBeAutobalanced(int client, bool origRet)
	{ return native_SDKHooksCanBeAutobalanced(client, origRet); }

// Callbacks
public Action ConCmdCallback(int client, int argc) { return native_ConCmdCallback(client, argc); }
public Action SrvCmdCallback(int argc) { return native_SrvCmdCallback(argc); }
public Action CmdListenerCallback(int client, const char[] command, int argc) { return native_CmdListenerCallback(client, command, argc); }
public void SQLTxnSuccessCallback(Database db, any data, int numQueries, DBResultSet[] results, any[] queryData) { native_SQLTxnSuccessCallback(db, data, numQueries, results, queryData); }
public void SQLTxnFailureCallback(Database db, any data, int numQueries, const char[] error, int failIndex, any[] queryData) { native_SQLTxnFailureCallback(db, data, numQueries, error, failIndex, queryData); }
public void SQLTCallbackConnectFunc(Handle owner, Handle hndl, const char[] error, int data) { native_SQLTCallbackConnect(owner, hndl, error, data); }
public void SQLTCallbackQueryFunc(Handle owner, Handle hndl, const char[] error, int data) { native_SQLTCallbackQuery(owner, hndl, error, data); }
public Action EventHookCallbackPre(Event event, const char[] name, bool dontBroadcast) { return native_EventHookCallbackPre(event, name, dontBroadcast); }
public Action EventHookCallbackPost(Event event, const char[] name, bool dontBroadcast) { return native_EventHookCallbackPost(event, name, dontBroadcast); }
public Action EventHookCallbackPostNoCopy(Event event, const char[] name, bool dontBroadcast) { return native_EventHookCallbackPostNoCopy(event, name, dontBroadcast); }
public int MenuHandlerCallback(Menu menu, MenuAction action, int param1, int param2) { return native_MenuHandlerCallback(menu, action, param1, param2); }
public void VoteHandlerCallback(Menu menu, int num_votes, int num_clients, const int[][] client_info, int num_items, const int[][] item_info)
	{ native_VoteHandlerCallback(menu, num_votes, num_clients, client_info, num_items, item_info); }

public Action TimerCallback(Handle timer, int data) { return native_TimerCallback(timer, data); }

public Action EntityOutputCallback(const char[] output, int caller, int activator, float delay) { return native_EntityOutputCallback(output, caller, activator, delay); }
public Action SingleEntityOutputCallback(const char[] output, int caller, int activator, float delay) { return native_SingleEntityOutputCallback(output, caller, activator, delay); }

public Action TEHookCallback(const char[] te_name, const int[] Players, int numClients, float delay) { return native_TEHookCallback(te_name, Players, numClients, delay); }

public Action GameLogHookCallback(const char[] message) { return native_GameLogHookCallback(message); }

public bool TraceEntityFilterCallback(int entity, int contentsMask, int data) { return native_TraceEntityFilterCallback(entity, contentsMask, data); }
public bool TraceEntityEnumeratorCallback(int entity, int data) { return native_TraceEntityEnumeratorCallback(entity, data); }

public bool MultiTargetFilterCallback(const char[] pattern, Handle clients) { return native_MultiTargetFilterCallback(pattern, clients); }

public Action AmbientSHookCallback(char sample[PLATFORM_MAX_PATH], int &entity, float &volume, int &level, int &pitch,
	float pos[3], int &flags, float &delay)
{
	return native_AmbientSHookCallback(sample, entity, volume, level, pitch, pos, flags, delay);
}

public Action NormalSHookCallback(int clients[MAXPLAYERS], int &numClients, char sample[PLATFORM_MAX_PATH], int &entity,
	int &channel, float &volume, int &level, int &pitch, int &flags, char soundEntry[PLATFORM_MAX_PATH], int &seed)
{
	return native_NormalSHookCallback(clients, numClients, sample, entity, channel, volume, level, pitch, flags, soundEntry, seed);
}

/* OWN */
public bool public_SDKCallSmoke3(Handle call, Address addr, float[] from, float[] to)
{
	return SDKCall(call, addr, from, to);
}
public bool public_SDKCallSmoke4(Handle call, Address addr, float[] from, float[] to, float arg)
{
	return SDKCall(call, addr, from, to, arg);
}

/* SOURCEMOD.INC */
// SOURCEMOD.INC - Natives
public void OnPluginStart()
{
	s_SDKHookCallbacks[SDKHook_EndTouch] = SDKHooksEndTouch;
	s_SDKHookCallbacks[SDKHook_FireBulletsPost] = SDKHooksFireBulletsPost;
	s_SDKHookCallbacks[SDKHook_OnTakeDamage] = SDKHooksOnTakeDamage;
	s_SDKHookCallbacks[SDKHook_OnTakeDamagePost] = SDKHooksOnTakeDamagePost;
	s_SDKHookCallbacks[SDKHook_PreThink] = SDKHooksPreThink;
	s_SDKHookCallbacks[SDKHook_PostThink] = SDKHooksPostThink;
	s_SDKHookCallbacks[SDKHook_SetTransmit] = SDKHooksSetTransmit;
	s_SDKHookCallbacks[SDKHook_Spawn] = SDKHooksSpawn;
	s_SDKHookCallbacks[SDKHook_StartTouch] = SDKHooksStartTouch;
	s_SDKHookCallbacks[SDKHook_Think] = SDKHooksThink;
	s_SDKHookCallbacks[SDKHook_Touch] = SDKHooksTouch;
	s_SDKHookCallbacks[SDKHook_TraceAttack] = SDKHooksTraceAttack;
	s_SDKHookCallbacks[SDKHook_TraceAttackPost] = SDKHooksTraceAttackPost;
	s_SDKHookCallbacks[SDKHook_WeaponCanSwitchTo] = SDKHooksWeaponCanSwitchTo;
	s_SDKHookCallbacks[SDKHook_WeaponCanUse] = SDKHooksWeaponCanUse;
	s_SDKHookCallbacks[SDKHook_WeaponDrop] = SDKHooksWeaponDrop;
	s_SDKHookCallbacks[SDKHook_WeaponEquip] = SDKHooksWeaponEquip;
	s_SDKHookCallbacks[SDKHook_WeaponSwitch] = SDKHooksWeaponSwitch;
	s_SDKHookCallbacks[SDKHook_ShouldCollide] = SDKHooksShouldCollide;
	s_SDKHookCallbacks[SDKHook_PreThinkPost] = SDKHooksPreThinkPost;
	s_SDKHookCallbacks[SDKHook_PostThinkPost] = SDKHooksPostThinkPost;
	s_SDKHookCallbacks[SDKHook_ThinkPost] = SDKHooksThinkPost;
	s_SDKHookCallbacks[SDKHook_EndTouchPost] = SDKHooksEndTouchPost;
	s_SDKHookCallbacks[SDKHook_GroundEntChangedPost] = SDKHooksGroundEntChanged;
	s_SDKHookCallbacks[SDKHook_SpawnPost] = SDKHooksSpawnPost;
	s_SDKHookCallbacks[SDKHook_StartTouchPost] = SDKHooksStartTouchPost;
	s_SDKHookCallbacks[SDKHook_TouchPost] = SDKHooksTouchPost;
	s_SDKHookCallbacks[SDKHook_VPhysicsUpdate] = SDKHooksVPhysicsUpdate;
	s_SDKHookCallbacks[SDKHook_VPhysicsUpdatePost] = SDKHooksVPhysicsUpdatePost;
	s_SDKHookCallbacks[SDKHook_WeaponCanSwitchToPost] = SDKHooksWeaponCanSwitchToPost;
	s_SDKHookCallbacks[SDKHook_WeaponCanUsePost] = SDKHooksWeaponCanUsePost;
	s_SDKHookCallbacks[SDKHook_WeaponDropPost] = SDKHooksWeaponDropPost;
	s_SDKHookCallbacks[SDKHook_WeaponEquipPost] = SDKHooksWeaponEquipPost;
	s_SDKHookCallbacks[SDKHook_WeaponSwitchPost] = SDKHooksWeaponSwitchPost;
	s_SDKHookCallbacks[SDKHook_Use] = SDKHooksUse;
	s_SDKHookCallbacks[SDKHook_UsePost] = SDKHooksUsePost;
	s_SDKHookCallbacks[SDKHook_Reload] = SDKHooksReload;
	s_SDKHookCallbacks[SDKHook_ReloadPost] = SDKHooksReloadPost;
	s_SDKHookCallbacks[SDKHook_GetMaxHealth] = SDKHooksGetMaxHealth;
	s_SDKHookCallbacks[SDKHook_Blocked] = SDKHooksBlocked;
	s_SDKHookCallbacks[SDKHook_BlockedPost] = SDKHooksBlockedPost;
	s_SDKHookCallbacks[SDKHook_OnTakeDamageAlive] = SDKHooksOnTakeDamageAlive;
	s_SDKHookCallbacks[SDKHook_OnTakeDamageAlivePost] = SDKHooksOnTakeDamageAlivePost;
	s_SDKHookCallbacks[SDKHook_CanBeAutobalanced] = SDKHooksCanBeAutobalanced;
	
	native_OnPluginStart();
}

public void OnPluginEnd() { native_OnPluginEnd(); }
public void OnPluginPauseChange(bool pause) { native_OnPluginPauseChange(pause); }
public void OnGameFrame() { native_OnGameFrame(); }
public void OnMapStart() { native_OnMapStart(); }
public void OnMapEnd() { native_OnMapEnd(); }
public void OnConfigsExecuted() { native_OnConfigsExecuted(); }
public void OnAutoConfigsBuffered() { native_OnAutoConfigsBuffered(); }
public void OnAllPluginsLoaded() { native_OnAllPluginsLoaded(); }
public void OnLibraryAdded(const char[] name) { native_OnLibraryAdded(name); }
public void OnLibraryRemoved(const char[] name) { native_OnLibraryRemoved(name); }
public bool OnClientFloodCheck(int client) { return native_OnClientFloodCheck(client); }
public void OnClientFloodResult(int client, bool blocked) { native_OnClientFloodResult(client, blocked); }
// SOURCEMOD.INC - Public
public Handle public_GetMyHandle() { return GetMyHandle(); }
public Handle public_GetPluginIterator() { return GetPluginIterator(); }
public bool public_MorePlugins(Handle iter) { return MorePlugins(iter); }
public Handle public_ReadPlugin(Handle iter) { return ReadPlugin(iter); }
public PluginStatus public_GetPluginStatus(Handle plugin) { return GetPluginStatus(plugin); }
public void public_GetPluginFilename(Handle plugin, char[] buffer, int maxlength) { GetPluginFilename(plugin, buffer, maxlength); }
public bool public_IsPluginDebugging(Handle plugin) { return IsPluginDebugging(plugin); }
public bool public_GetPluginInfo(Handle plugin, PluginInfo info, char[] buffer, int maxlength) { return GetPluginInfo(plugin, info, buffer, maxlength); }
public Handle public_FindPluginByNumber(int order_num) { return FindPluginByNumber(order_num); }
public void public_SetFailState(const char[] string, any ...)
{
	char buffer[512];
	VFormat(buffer, sizeof(buffer), string, 2);
	SetFailState(buffer);
}
public void public_ThrowError(const char[] fmt, any ...)
{
	char buffer[512];
	VFormat(buffer, sizeof(buffer), fmt, 2);
	ThrowError(buffer);
}
public void public_LogStackTrace(const char[] fmt, any ...)
{
	char buffer[512];
	VFormat(buffer, sizeof(buffer), fmt, 2);
	LogStackTrace(buffer);
}
public int public_GetTime(int bigStamp[2]) { return GetTime(bigStamp); }
public void public_FormatTime(char[] buffer, int maxlength, const char[] format, int stamp) { FormatTime(buffer, maxlength, format, stamp); }
public GameData public_LoadGameConfigFile(const char[] file) { return LoadGameConfigFile(file); }
public int public_GameConfGetOffset(Handle gc, const char[] key) { return GameConfGetOffset(gc, key); }
public bool public_GameConfGetKeyValue(Handle gc, const char[] key, char[] buffer, int maxlen) { return GameConfGetKeyValue(gc, key, buffer, maxlen); }
public Address public_GameConfGetAddress(Handle gameconf, const char[] name) { return GameConfGetAddress(gameconf, name); }
public int public_GetSysTickCount() { return GetSysTickCount(); }
public void public_AutoExecConfig(bool autoCreate, const char[] name, const char[] folder) { AutoExecConfig(autoCreate, name, folder); }
public void public_RegPluginLibrary(const char[] name) { RegPluginLibrary(name); }
public bool public_LibraryExists(const char[] name) { return LibraryExists(name); }
public int public_GetExtensionFileStatus(const char[] name, char[] error , int maxlength) { return GetExtensionFileStatus(name, error, maxlength); }
public Handle public_ReadMapList(Handle array, int &serial, const char[] str, int flags) { return ReadMapList(array, serial, str, flags); }
public void public_SetMapListCompatBind(const char[] name, const char[] file) { SetMapListCompatBind(name, file); }
public FeatureStatus public_GetFeatureStatus(FeatureType type, const char[] name) { return GetFeatureStatus(type, name); }
public void public_RequireFeature(FeatureType type, const char[] name, const char[] fmt, any ...)
{
	char buffer[128];
	VFormat(buffer, sizeof(buffer), fmt, 4);
	RequireFeature(type, name, buffer);
}
public any public_LoadFromAddress(Address addr, NumberType size) { return LoadFromAddress(addr, size); }
public void public_StoreToAddress(Address addr, any data, NumberType size) { StoreToAddress(addr, data, size); }

/* SDKTOOLS.INC */
// SDKTOOLS_INC - Public
public void public_StartPrepSDKCall(SDKCallType type) { StartPrepSDKCall(type); }
public void public_PrepSDKCall_SetVirtual(int vtblidx) { PrepSDKCall_SetVirtual(vtblidx); }
public bool public_PrepSDKCall_SetSignature(SDKLibrary lib, const char[] signature, int bytes) { return PrepSDKCall_SetSignature(lib, signature, bytes); }
public bool public_PrepSDKCall_SetAddress(Address addr) { return PrepSDKCall_SetAddress(addr); }
public bool public_PrepSDKCall_SetFromConf(Handle gameconf, SDKFuncConfSource source, const char[] name) { return PrepSDKCall_SetFromConf(gameconf, source, name); }
public void public_PrepSDKCall_SetReturnInfo(SDKType type, SDKPassMethod pass, int decflags, int encflags) { PrepSDKCall_SetReturnInfo(type, pass, decflags, encflags); }
public void public_PrepSDKCall_AddParameter(SDKType type, SDKPassMethod pass, int decflags, int encflags) { PrepSDKCall_AddParameter(type, pass, decflags, encflags); }
public Handle public_EndPrepSDKCall() { return EndPrepSDKCall(); }
public any public_SDKCall0(Handle call)
{
	return SDKCall(call);
}
public any public_SDKCall1(Handle call, any arg1)
{
	return SDKCall(call, arg1);
}
public any public_SDKCall2(Handle call, any arg1, any arg2)
{
	return SDKCall(call, arg1, arg2);
}
public any public_SDKCall3(Handle call, any arg1, any arg2, any arg3)
{
	return SDKCall(call, arg1, arg2, arg3);
}
public any public_SDKCall4(Handle call, any arg1, any arg2, any arg3, any arg4)
{
	return SDKCall(call, arg1, arg2, arg3, arg4);
}
public any public_SDKCall5(Handle call, any arg1, any arg2, any arg3, any arg4, any arg5)
{
	return SDKCall(call, arg1, arg2, arg3, arg4, arg5);
}
public any public_SDKCall6(Handle call, any arg1, any arg2, any arg3, any arg4, any arg5, any arg6)
{
	return SDKCall(call, arg1, arg2, arg3, arg4, arg5, arg6);
}
public any public_SDKCall7(Handle call, any arg1, any arg2, any arg3, any arg4, any arg5, any arg6, any arg7)
{
	return SDKCall(call, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
}
public any public_SDKCall8(Handle call, any arg1, any arg2, any arg3, any arg4, any arg5, any arg6, any arg7, any arg8)
{
	return SDKCall(call, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
}
public any public_SDKCall9(Handle call, any arg1, any arg2, any arg3, any arg4, any arg5, any arg6, any arg7, any arg8, any arg9)
{
	return SDKCall(call, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}
public any public_SDKCall10(Handle call, any arg1, any arg2, any arg3, any arg4, any arg5, any arg6, any arg7, any arg8, any arg9, any arg10)
{
	return SDKCall(call, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10);
}
public int public_GetPlayerResourceEntity() { return GetPlayerResourceEntity(); }

/* SDKTOOLS_SOUND.INC */
// SDKTOOLS_SOUND.INC - Public
public void public_PrefetchSound(const char[] name) { PrefetchSound(name); }
public void public_EmitAmbientSound(const char[] name, const float pos[3], int entity, int level, int flags, float vol, int pitch, float delay)
{
	EmitAmbientSound(name, pos, entity, level, flags, vol, pitch, delay);
}
public void public_FadeClientVolume(int client, float percent, float outtime, float holdtime, float intime)
{
	FadeClientVolume(client, percent, outtime, holdtime, intime);
}
public void public_StopSound(int entity, int channel, const char[] name)
{
	StopSound(entity, channel, name);
}
public void public_EmitSound(const int[] clients, int numClients, const char[] sample, int entity, int channel, int level, int flags,
	float volume, int pitch, int speakerentity, const float origin[3], const float dir[3], bool updatePos, float soundtime)
{
	EmitSound(clients, numClients, sample, entity, channel, level, flags, volume, pitch, speakerentity, origin, dir, updatePos, soundtime);
}
public void public_EmitSoundEntry(const int[] clients, int numClients, const char[] soundEntry, const char[] sample, int entity, int channel,
	int level, int seed, int flags, float volume, int pitch, int speakerentity, const float origin[3], const float dir[3],
	bool updatePos, float soundtime)
{
	EmitSoundEntry(clients, numClients, soundEntry, sample, entity, channel, level, seed, flags, volume, pitch, speakerentity, origin, dir, updatePos, soundtime);
}
public void public_EmitSentence(const int[] clients, int numClients, int sentence, int entity, int channel, int level,
	int flags, float volume, int pitch, int speakerentity, const float origin[3],
	const float dir[3], bool updatePos, float soundtime)
{
	EmitSentence(clients, numClients, sentence, entity, channel, level, flags, volume, pitch, speakerentity, origin, dir, updatePos, soundtime);
}
public float public_GetDistGainFromSoundLevel(int soundlevel, float distance) {}
public void public_AddAmbientSoundHook() { AddAmbientSoundHook(AmbientSHookCallback); }
public void public_AddNormalSoundHook() { AddNormalSoundHook(NormalSHookCallback); }
public void public_RemoveAmbientSoundHook() { RemoveAmbientSoundHook(AmbientSHookCallback); }
public void public_RemoveNormalSoundHook() { RemoveNormalSoundHook(NormalSHookCallback); }
public bool public_GetGameSoundParams(const char[] gameSound, int &channel, int &soundLevel, float &volume,
	int &pitch, char[] sample, int maxlength, int entity)
{
	return GetGameSoundParams(gameSound, channel, soundLevel, volume, pitch, sample, maxlength, entity);
}
public bool public_PrecacheScriptSound(const char[] soundname) { return PrecacheScriptSound(soundname); }

/* COMMANDFILTERS.INC */
// COMMANDFILTERS.INC - Public
public int public_ProcessTargetString(const char[] pattern, int admin,  int[] targets, int max_targets, int filter_flags, char[] target_name, int tn_maxlength, bool &tn_is_ml)
{
	return ProcessTargetString(pattern, admin, targets, max_targets, filter_flags, target_name, tn_maxlength, tn_is_ml);
}
public void public_AddMultiTargetFilter(const char[] pattern, const char[] phrase, bool phraseIsML)
{
	AddMultiTargetFilter(pattern, MultiTargetFilterCallback, phrase, phraseIsML);
}
public void public_RemoveMultiTargetFilter(const char[] pattern)
{
	RemoveMultiTargetFilter(pattern, MultiTargetFilterCallback);
}

/* ADT_Array */
// ADT_Array - Public
public ArrayList public_CreateArray(int blocksize, int startsize) { return CreateArray(blocksize, startsize); }
public void public_ClearArray(Handle array) { ClearArray(array); }
public Handle public_CloneArray(Handle array) { return CloneArray(array); }
public void public_ResizeArray(Handle array, int newsize) { ResizeArray(array, newsize); }
public int public_GetArraySize(Handle array) { return GetArraySize(array); }
public int public_PushArrayCell(Handle array, any value) { return PushArrayCell(array, value); }
public int public_PushArrayString(Handle array, const char[] value) { return PushArrayString(array, value); }
public int public_PushArrayArray(Handle array, const any[] values, int size) { return PushArrayArray(array, values, size); }
public any public_GetArrayCell(Handle array, int index, int block, bool asChar) { return GetArrayCell(array, index, block, asChar); }
public int public_GetArrayString(Handle array, int index, char[] buffer, int maxlength) { return GetArrayString(array, index, buffer, maxlength); }
public int public_GetArrayArray(Handle array, int index, any[] buffer, int size) { return GetArrayArray(array, index, buffer, size); }
public void public_SetArrayCell(Handle array, int index, any value, int block, bool asChar) { SetArrayCell(array, index, value, block, asChar); }
public int public_SetArrayString(Handle array, int index, const char[] value) { return SetArrayString(array, index, value); }
public int public_SetArrayArray(Handle array, int index, const any[] values, int size) { return SetArrayArray(array, index, values, size); }
public void public_ShiftArrayUp(Handle array, int index) { ShiftArrayUp(array, index); }
public void public_RemoveFromArray(Handle array, int index) { RemoveFromArray(array, index); }
public void public_SwapArrayItems(Handle array, int index1, int index2) { SwapArrayItems(array, index1, index2); }
public int public_FindStringInArray(Handle array, const char[] item) { return FindStringInArray(array, item); }
public int public_FindValueInArray(Handle array, any item, int block) { return FindValueInArray(array, item, block); }
public int public_GetArrayBlockSize(Handle array) { return GetArrayBlockSize(array); }

/* LANG.INC */
// LANG.INC - Public
public void public_LoadTranslations(const char[] file) { LoadTranslations(file); }
public void public_SetGlobalTransTarget(int client) { SetGlobalTransTarget(client); }
public int public_GetClientLanguage(int client) { return GetClientLanguage(client); }
public int public_GetServerLanguage() { return GetServerLanguage(); }
public int public_GetLanguageCount() { return GetLanguageCount(); }
public void public_GetLanguageInfo(int language, char[] code, int codeLen, char[] name, int nameLen) { GetLanguageInfo(language, code, codeLen, name, nameLen); }
public void public_SetClientLanguage(int client, int language) { SetClientLanguage(client, language); }
public int public_GetLanguageByCode(const char[] code) { return GetLanguageByCode(code); }
public int public_GetLanguageByName(const char[] name) { return GetLanguageByName(name); }
public bool public_TranslationPhraseExists(const char[] phrase) { return TranslationPhraseExists(phrase); }
public bool public_IsTranslatedForLanguage(const char[] phrase, int language) { return IsTranslatedForLanguage(phrase, language); }

/* SDKTOOLS_VOICE.INC */
// SDKTOOLS_VOICE.INC - Natives
public void OnClientSpeaking(int client) { native_OnClientSpeaking(client); }
public void OnClientSpeakingEnd(int client) { native_OnClientSpeakingEnd(client); }
// SDKTOOLS_VOICE.INC - Public
public void public_SetClientListeningFlags(int client, int flags) { SetClientListeningFlags(client, flags); }
public int public_GetClientListeningFlags(int client) { return GetClientListeningFlags(client); }
public bool public_SetListenOverride(int iReceiver, int iSender, ListenOverride override) { return SetListenOverride(iReceiver, iSender, override); }
public ListenOverride public_GetListenOverride(int iReceiver, int iSender) { return GetListenOverride(iReceiver, iSender); }
public bool public_IsClientMuted(int iMuter, int iMutee) { return IsClientMuted(iMuter, iMutee); }

/* STRING.INC */
// STRING.INC - Public
public int public_Format(char[] buffer, int maxlength, const char[] format, any ...) { return VFormat(buffer, maxlength, format, 4); }

/* SDKTOOLS_CLIENT.INC */
// SDKTOOLS_CLIENT.INC - Public
public void public_InactivateClient(int client) { InactivateClient(client); }
public void public_ReconnectClient(int client) { ReconnectClient(client); }

/* SDKTOOLS_ENGINE.INC */
// SDKTOOLS_ENGINE.INC - Public
public void public_SetClientViewEntity(int client, int entity) { SetClientViewEntity(client, entity); }
public void public_SetLightStyle(int style, const char[] value) { SetLightStyle(style, value); }
public void public_GetClientEyePosition(int client, float pos[3]) { GetClientEyePosition(client, pos); }

/* SDKTOOLS_TRACE.INC */
// SDKTOOLS_TRACE.INC - Public
public int public_TR_GetPointContents(const float pos[3], int &entindex)
{
	return TR_GetPointContents(pos, entindex);
}
public int public_TR_GetPointContentsEnt(int entindex, const float pos[3])
{
	return TR_GetPointContentsEnt(entindex, pos);
}
public void public_TR_TraceRay(const float pos[3], const float vec[3], int flags, RayType rtype)
{
	TR_TraceRay(pos, vec, flags, rtype);
}
public void public_TR_TraceHull(const float pos[3], const float vec[3], const float mins[3], const float maxs[3], int flags)
{
	TR_TraceHull(pos, vec, mins, maxs, flags);
}
public void public_TR_EnumerateEntities(const float pos[3], const float vec[3], int mask, RayType rtype, int data)
{
	TR_EnumerateEntities(pos, vec, mask, rtype, TraceEntityEnumeratorCallback, data);
}
public void public_TR_EnumerateEntitiesHull(const float pos[3], const float vec[3], const float mins[3], const float maxs[3], int mask, int data)
{
	TR_EnumerateEntitiesHull(pos, vec, mins, maxs, mask, TraceEntityEnumeratorCallback, data);
}
public void public_TR_EnumerateEntitiesSphere(const float pos[3], float radius, int mask, int data)
{
	TR_EnumerateEntitiesSphere(pos, radius, mask, TraceEntityEnumeratorCallback, data);
}
public void public_TR_EnumerateEntitiesBox(const float mins[3], const float maxs[3], int mask, int data)
{
	TR_EnumerateEntitiesBox(mins, maxs, mask, TraceEntityEnumeratorCallback, data);
}
public void public_TR_EnumerateEntitiesPoint(const float pos[3], int mask, int data)
{
	TR_EnumerateEntitiesPoint(pos, mask, TraceEntityEnumeratorCallback, data);
}
public void public_TR_TraceRayFilter(const float pos[3], const float vec[3], int flags, RayType rtype, int data)
{
	TR_TraceRayFilter(pos, vec, flags, rtype, TraceEntityFilterCallback, data);
}
public void public_TR_TraceHullFilter(const float pos[3], const float vec[3], const float mins[3], const float maxs[3], int flags, int data)
{
	TR_TraceHullFilter(pos, vec, mins, maxs, flags, TraceEntityFilterCallback, data);
}
public void public_TR_ClipRayToEntity(const float pos[3], const float vec[3], int flags, RayType rtype, int entity)
{
	TR_ClipRayToEntity(pos, vec, flags, rtype, entity);
}
public void public_TR_ClipRayHullToEntity(const float pos[3], const float vec[3], const float mins[3], const float maxs[3], int flags, int entity)
{
	TR_ClipRayHullToEntity(pos, vec, mins, maxs, flags, entity);
}
public void public_TR_ClipCurrentRayToEntity(int flags, int entity)
{
	TR_ClipCurrentRayToEntity(flags, entity);
}
public Handle public_TR_TraceRayEx(const float pos[3], const float vec[3], int flags, RayType rtype)
{
	return TR_TraceRayEx(pos, vec, flags, rtype);
}
public Handle public_TR_TraceHullEx(const float pos[3], const float vec[3], const float mins[3], const float maxs[3], int flags)
{
	return TR_TraceHullEx(pos, vec, mins, maxs, flags);
}
public Handle public_TR_TraceRayFilterEx(const float pos[3], const float vec[3], int flags, RayType rtype, int data)
{
	return TR_TraceRayFilterEx(pos, vec, flags, rtype, TraceEntityFilterCallback, data);
}
public Handle public_TR_TraceHullFilterEx(const float pos[3], const float vec[3], const float mins[3], const float maxs[3], int flags, int data)
{
	return TR_TraceHullFilterEx(pos, vec, mins, maxs, flags, TraceEntityFilterCallback, data);
}
public Handle public_TR_ClipRayToEntityEx(const float pos[3], const float vec[3], int flags, RayType rtype, int entity)
{
	return TR_ClipRayToEntityEx(pos, vec, flags, rtype, entity);
}
public Handle public_TR_ClipRayHullToEntityEx(const float pos[3], const float vec[3], const float mins[3], const float maxs[3], int flags, int entity)
{
	return TR_ClipRayHullToEntityEx(pos, vec, mins, maxs, flags, entity);
}
public Handle public_TR_ClipCurrentRayToEntityEx(int flags, int entity)
{
	return TR_ClipCurrentRayToEntityEx(flags, entity);
}
public float public_TR_GetFraction(Handle hndl)
{
	return TR_GetFraction(hndl);
}
public float public_TR_GetFractionLeftSolid(Handle hndl)
{
	return TR_GetFractionLeftSolid(hndl);
}
public void public_TR_GetStartPosition(Handle hndl, float pos[3])
{
	TR_GetStartPosition(hndl, pos);
}
public void public_TR_GetEndPosition(float pos[3], Handle hndl)
{
	TR_GetEndPosition(pos, hndl);
}
public int public_TR_GetEntityIndex(Handle hndl)
{
	return TR_GetEntityIndex(hndl);
}
public int public_TR_GetDisplacementFlags(Handle hndl)
{
	return TR_GetDisplacementFlags(hndl);
}
public void public_TR_GetSurfaceName(Handle hndl, char[] buffer, int maxlen)
{
	TR_GetSurfaceName(hndl, buffer, maxlen);
}
public int public_TR_GetSurfaceProps(Handle hndl)
{
	return TR_GetSurfaceProps(hndl);
}
public int public_TR_GetSurfaceFlags(Handle hndl)
{
	return TR_GetSurfaceFlags(hndl);
}
public int public_TR_GetPhysicsBone(Handle hndl)
{
	return TR_GetPhysicsBone(hndl);
}
public bool public_TR_AllSolid(Handle hndl)
{
	return TR_AllSolid(hndl);
}
public bool public_TR_StartSolid(Handle hndl)
{
	return TR_StartSolid(hndl);
}
public bool public_TR_DidHit(Handle hndl)
{
	return TR_DidHit(hndl);
}
public int public_TR_GetHitGroup(Handle hndl)
{
	return TR_GetHitGroup(hndl);
}
public int public_TR_GetHitBoxIndex(Handle hndl)
{
	return TR_GetHitBoxIndex(hndl);
}
public void public_TR_GetPlaneNormal(Handle hndl, float normal[3])
{
	TR_GetPlaneNormal(hndl, normal);
}
public bool public_TR_PointOutsideWorld(float pos[3])
{
	return TR_PointOutsideWorld(pos);
}

/* LOGGING.INC */
// LOGGING.INC - Natives
public Action OnLogAction(Handle source, Identity ident, int client, int target, const char[] message)
{
	return native_OnLogAction(source, ident, client, target, message);
}
// LOGGING.INC - Public
public void public_LogMessage(const char[] format, any ...)
{
	char buffer[512];
	VFormat(buffer, sizeof(buffer), format, 2);
	LogMessage(buffer);
}
public void public_LogToFile(const char[] file, const char[] format, any ...)
{
	char buffer[512];
	VFormat(buffer, sizeof(buffer), format, 3);
	LogToFile(file, buffer);
}
public void public_LogToFileEx(const char[] file, const char[] format, any ...)
{
	char buffer[512];
	VFormat(buffer, sizeof(buffer), format, 3);
	LogToFileEx(file, buffer);
}
public void public_LogAction(int client, int target, const char[] message, any ...)
{
	char buffer[512];
	VFormat(buffer, sizeof(buffer), message, 4);
	LogAction(client, target, buffer);
}
public void public_LogError(const char[] format, any ...)
{
	char buffer[512];
	VFormat(buffer, sizeof(buffer), format, 2);
	LogError(buffer);
}
public void public_AddGameLogHook() { AddGameLogHook(GameLogHookCallback); }
public void public_RemoveGameLogHook(GameLogHook hook) { RemoveGameLogHook(GameLogHookCallback); }

/* SDKTOOLS_TEMPENTS.INC */
// SDKTOOLS_TEMPENTS.INC - Public
public void public_AddTempEntHook(const char[] te_name) { AddTempEntHook(te_name, TEHookCallback); }
public void public_RemoveTempEntHook(const char[] te_name) { RemoveTempEntHook(te_name, TEHookCallback); }
public void public_TE_Start(const char[] te_name) { TE_Start(te_name); }
public bool public_TE_IsValidProp(const char[] prop) { return TE_IsValidProp(prop); }
public void public_TE_WriteNum(const char[] prop, int value) { TE_WriteNum(prop, value); }
public int public_TE_ReadNum(const char[] prop) { return TE_ReadNum(prop); }
public void public_TE_WriteFloat(const char[] prop, float value) { TE_WriteFloat(prop, value); }
public float public_TE_ReadFloat(const char[] prop) { return TE_ReadFloat(prop); }
public void public_TE_WriteVector(const char[] prop, const float vector[3]) { TE_WriteVector(prop, vector); }
public void public_TE_ReadVector(const char[] prop, float vector[3]) { TE_ReadVector(prop, vector); }
public void public_TE_WriteAngles(const char[] prop, const float angles[3]) { TE_WriteAngles(prop, angles); }
public void public_TE_WriteFloatArray(const char[] prop, const float[] array, int arraySize) { TE_WriteFloatArray(prop, array, arraySize); }
public void public_TE_Send(const int[] clients, int numClients, float delay) { TE_Send(clients, numClients, delay); }

/* SDKTOOLS_GAMERULES.INC */
// SDKTOOLS_GAMERULES.INC - Public
public int public_GameRules_GetProp(const char[] prop, int size, int element) { return GameRules_GetProp(prop, size, element); }
public void public_GameRules_SetProp(const char[] prop, any value, int size, int element, bool changeState) { GameRules_SetProp(prop, value, size, element, changeState); }
public float public_GameRules_GetPropFloat(const char[] prop, int element) { return GameRules_GetPropFloat(prop, element); }
public void public_GameRules_SetPropFloat(const char[] prop, float value, int element, bool changeState) { GameRules_SetPropFloat(prop, value, element, changeState); }
public int public_GameRules_GetPropEnt(const char[] prop, int element) { return GameRules_GetPropEnt(prop, element); }
public void public_GameRules_SetPropEnt(const char[] prop, int other, int element, bool changeState) { GameRules_SetPropEnt(prop, other, element, changeState); }
public void public_GameRules_GetPropVector(const char[] prop, float vec[3], int element) { GameRules_GetPropVector(prop, vec, element); }
public void public_GameRules_SetPropVector(const char[] prop, const float vec[3], int element, bool changeState) { GameRules_SetPropVector(prop, vec, element, changeState); }
public int public_GameRules_GetPropString(const char[] prop, char[] buffer, int maxlen) { return GameRules_GetPropString(prop, buffer, maxlen); }
public int public_GameRules_SetPropString(const char[] prop, const char[] buffer, bool changeState) { return GameRules_SetPropString(prop, buffer, changeState); }

/* SDKTOOLS_ENTINPUT.INC */
// SDKTOOLS_ENTINPUT.INC - Public
public bool public_AcceptEntityInput(int dest, const char[] input, int activator, int caller, int outputid) { return AcceptEntityInput(dest, input, activator, caller, outputid); }

/* SDKTOOLS_ENTOUTPUT.INC */
// SDKTOOLS_ENTOUTPUT.INC - Public
public void public_HookEntityOutput(const char[] classname, const char[] output) { HookEntityOutput(classname, output, EntityOutputCallback); }
public bool public_UnhookEntityOutput(const char[] classname, const char[] output) { return UnhookEntityOutput(classname, output, EntityOutputCallback); }
public void public_HookSingleEntityOutput(int entity, const char[] output, bool once) { HookSingleEntityOutput(entity, output, SingleEntityOutputCallback, once); }
public bool public_UnhookSingleEntityOutput(int entity, const char[] output) { return UnhookSingleEntityOutput(entity, output, SingleEntityOutputCallback); }
public void public_FireEntityOutput(int caller, const char[] output, int activator, float delay) { FireEntityOutput(caller, output, activator, delay); }

/* HANDLES.INC */
// HANDLES.INC - Public
public void public_CloseHandle(Handle hndl) { CloseHandle(hndl); }
public Handle public_CloneHandle(Handle hndl, Handle plugin) { return CloneHandle(hndl, plugin); }

/* ENTITY_PROP_STOCKS.INC */
// ENTITY_PROP_STOCKS.INC - Public
public int public_GetEntityFlags(int entity) { return GetEntityFlags(entity); }
public void public_SetEntityFlags(int entity, int flags) { SetEntityFlags(entity, flags); }
public MoveType public_GetEntityMoveType(int entity) { return GetEntityMoveType(entity); }
public void public_SetEntityMoveType(int entity, MoveType mt) { SetEntityMoveType(entity, mt); }
public RenderMode public_GetEntityRenderMode(int entity) { return GetEntityRenderMode(entity); }
public void public_SetEntityRenderMode(int entity, RenderMode mode) { SetEntityRenderMode(entity, mode); }
public RenderFx public_GetEntityRenderFx(int entity) { return GetEntityRenderFx(entity); }
public void public_SetEntityRenderFx(int entity, RenderFx fx) { SetEntityRenderFx(entity, fx); }
public void public_GetEntityRenderColor(int entity, int &r, int &g, int &b, int &a) { GetEntityRenderColor(entity, r, g, b, a); }
public void public_SetEntityRenderColor(int entity, int r, int g, int b, int a) { SetEntityRenderColor(entity, r, g, b, a); }
public float public_GetEntityGravity(int entity) { return GetEntityGravity(entity); }
public void public_SetEntityGravity(int entity, float amount) { SetEntityGravity(entity, amount); }
public void public_SetEntityHealth(int entity, int amount) { SetEntityHealth(entity, amount); }
public int public_GetClientButtons(int client) { return GetClientButtons(client); }

/* HALFLIFE.INC */
// HALFLIFE.INC - Public
public void public_LogToGame(const char[] format, any ...)
{
	char buffer[512];
	VFormat(buffer, sizeof(buffer), format, 2);
	LogToGame(buffer);
}
public void public_SetRandomSeed(int seed) { SetRandomSeed(seed); }
public bool public_IsMapValid(const char[] map) { return IsMapValid(map); }
public FindMapResult public_FindMap(const char[] map, char[] foundmap, int maxlen) { return FindMap(map, foundmap, maxlen); }
public bool public_GetMapDisplayName(const char[] map, char[] displayName, int maxlen) { return GetMapDisplayName(map, displayName, maxlen); }
public bool public_IsDedicatedServer() { return IsDedicatedServer(); }
public float public_GetEngineTime() { return GetEngineTime(); }
public float public_GetGameTime() { return GetGameTime(); }
public int public_GetGameTickCount() { return GetGameTickCount(); }
public float public_GetGameFrameTime() { return GetGameFrameTime(); }
public int public_GetGameDescription(char[] buffer, int maxlength, bool original) { return GetGameDescription(buffer, maxlength, original); }
public int public_GetGameFolderName(char[] buffer, int maxlength) { return GetGameFolderName(buffer, maxlength); }
public int public_GetCurrentMap(char[] buffer, int maxlength) { return GetCurrentMap(buffer, maxlength); }
public int public_PrecacheModel(const char[] model, bool preload) { return PrecacheModel(model, preload); }
public int public_PrecacheSentenceFile(const char[] file, bool preload) { return PrecacheSentenceFile(file, preload); }
public int public_PrecacheDecal(const char[] decal, bool preload) { return PrecacheDecal(decal, preload); }
public int public_PrecacheGeneric(const char[] generic, bool preload) { return PrecacheGeneric(generic, preload); }
public bool public_IsModelPrecached(const char[] model) { return IsModelPrecached(model); }
public bool public_IsDecalPrecached(const char[] decal) { return IsDecalPrecached(decal); }
public bool public_IsGenericPrecached(const char[] generic) { return IsGenericPrecached(generic); }
public bool public_PrecacheSound(const char[] sound, bool preload) { return PrecacheSound(sound, preload); }
public void public_CreateDialog(int client, Handle kv, DialogType type) { CreateDialog(client, kv, type); }
public EngineVersion public_GetEngineVersion() { return GetEngineVersion(); }
public void public_PrintToChat(int client, const char[] format, any ...)
{
	char buffer[512];
	VFormat(buffer, sizeof(buffer), format, 3);
	PrintToChat(client, buffer);
}
public void public_PrintCenterText(int client, const char[] format, any ...)
{
	char buffer[512];
	VFormat(buffer, sizeof(buffer), format, 3);
	PrintCenterText(client, buffer);
}
public void public_PrintHintText(int client, const char[] format, any ...)
{
	char buffer[512];
	VFormat(buffer, sizeof(buffer), format, 3);
	PrintHintText(client, buffer);
}
public void public_ShowVGUIPanel(int client, const char[] name, Handle Kv, bool show) { ShowVGUIPanel(client, name, Kv, show); }
public Handle public_CreateHudSynchronizer() { return CreateHudSynchronizer(); }
public void public_SetHudTextParams(float x, float y, float holdTime, int r, int g, int b, int a, int effect, float fxTime, float fadeIn, float fadeOut)
{
	SetHudTextParams(x, y, holdTime, r, g, b, a, effect, fxTime, fadeIn, fadeOut);
}
public void public_SetHudTextParamsEx(float x, float y, float holdTime, int color1[4], int color2[4], int effect, float fxTime, float fadeIn, float fadeOut)
{
	SetHudTextParamsEx(x, y, holdTime, color1, color2, effect, fxTime, fadeIn, fadeOut);
}
public int public_ShowSyncHudText(int client, Handle sync, const char[] message, any ...)
{
	char buffer[512];
	VFormat(buffer, sizeof(buffer), message, 4);
	return ShowSyncHudText(client, sync, buffer);
}
public void public_ClearSyncHud(int client, Handle sync) { ClearSyncHud(client, sync); }
public int public_ShowHudText(int client, int channel, const char[] message, any ...)
{
	char buffer[512];
	VFormat(buffer, sizeof(buffer), message, 4);
	return ShowHudText(client, channel, buffer);
}
public int public_EntIndexToEntRef(int entity) { return EntIndexToEntRef(entity); }
public int public_EntRefToEntIndex(int ref) { return EntRefToEntIndex(ref); }
public int public_MakeCompatEntRef(int ref) { return MakeCompatEntRef(ref); }
public int public_GetClientsInRange(const float origin[3], ClientRangeType rangeType, int[] clients, int size)
{
	return GetClientsInRange(origin, rangeType, clients, size);
}
public void public_GetServerAuthId(AuthIdType authType, char[] auth, int maxlen) { GetServerAuthId(authType, auth, maxlen); }
public int public_GetServerSteamAccountId() { return GetServerSteamAccountId(); }

/* TIMERS.INC */
// TIMERS.INC - Natives
public void OnMapTimeLeftChanged() { native_OnMapTimeLeftChanged(); }
// TIMERS.INC - Public
public Handle public_CreateTimer(float interval, int data, int flags) { return CreateTimer(interval, TimerCallback, data, flags); }
public void public_KillTimer(Handle timer, bool autoClose) { KillTimer(timer, autoClose); }
public void public_TriggerTimer(Handle timer, bool reset) { TriggerTimer(timer, reset); }
public float public_GetTickedTime() { return GetTickedTime(); }
public bool public_GetMapTimeLeft(int &timeleft) { return GetMapTimeLeft(timeleft); }
public bool public_GetMapTimeLimit(int &time) { return GetMapTimeLimit(time); }
public bool public_ExtendMapTimeLimit(int time) { return ExtendMapTimeLimit(time); }
public float public_GetTickInterval() { return GetTickInterval(); }
public bool public_IsServerProcessing() { return IsServerProcessing(); }

// ENTITY.INC
public int public_GetMaxEntities() { return GetMaxEntities(); }
public int public_GetEntityCount() { return GetEntityCount(); }
public bool public_IsValidEntity(int entity) { return IsValidEntity(entity); }
public bool public_IsValidEdict(int edict) { return IsValidEdict(edict); }
public bool public_IsEntNetworkable(int entity) { return IsEntNetworkable(entity); }
public int public_CreateEdict() { return CreateEdict(); }
public void public_RemoveEdict(int edict) { RemoveEdict(edict); }
public void public_RemoveEntity(int entity) { RemoveEntity(entity); }
public int public_GetEdictFlags(int edict) { return GetEdictFlags(edict); }
public void public_SetEdictFlags(int edict, int flags) { SetEdictFlags(edict, flags); }
public bool public_GetEdictClassname(int edict, char[] clsname, int maxlength) { return GetEdictClassname(edict, clsname, maxlength); }
public bool public_GetEntityNetClass(int edict, char[] clsname, int maxlength) { return GetEntityNetClass(edict, clsname, maxlength); }
public void public_ChangeEdictState(int edict, int offset) { ChangeEdictState(edict, offset); }
public int public_GetEntData(int entity, int offset, int size) { return GetEntData(entity, offset, size); }
public void public_SetEntData(int entity, int offset, any value, int size, bool changeState) { SetEntData(entity, offset, value, size, changeState); }
public float public_GetEntDataFloat(int entity, int offset) { return GetEntDataFloat(entity, offset); }
public void public_SetEntDataFloat(int entity, int offset, float value, bool changeState) { SetEntDataFloat(entity, offset, value, changeState); }
public int public_GetEntDataEnt2(int entity, int offset) { return GetEntDataEnt2(entity, offset); }
public void public_SetEntDataEnt2(int entity, int offset, int other, bool changeState) { SetEntDataEnt2(entity, offset, other, changeState); }
public void public_GetEntDataVector(int entity, int offset, float vec[3]) { GetEntDataVector(entity, offset, vec); }
public void public_SetEntDataVector(int entity, int offset, const float vec[3], bool changeState) { SetEntDataVector(entity, offset, vec, changeState); }
public int public_GetEntDataString(int entity, int offset, char[] buffer, int maxlen) { return GetEntDataString(entity, offset, buffer, maxlen); }
public int public_SetEntDataString(int entity, int offset, const char[] buffer, int maxlen, bool changeState) { return SetEntDataString(entity, offset, buffer, maxlen, changeState); }
public int public_FindSendPropInfo(const char[] cls, const char[] prop, PropFieldType &type, int &num_bits, int &local_offset) { return FindSendPropInfo(cls, prop, type, num_bits, local_offset); }
public int public_FindDataMapInfo(int entity, const char[] prop, PropFieldType &type, int &num_bits, int &local_offset) { return FindDataMapInfo(entity, prop, type, num_bits, local_offset); }
public int public_GetEntProp(int entity, PropType type, const char[] prop, int size, int element) { return GetEntProp(entity, type, prop, size, element); }
public void public_SetEntProp(int entity, PropType type, const char[] prop, any value, int size, int element) { SetEntProp(entity, type, prop, value, size, element); }
public float public_GetEntPropFloat(int entity, PropType type, const char[] prop, int element) { return GetEntPropFloat(entity, type, prop, element); }
public void public_SetEntPropFloat(int entity, PropType type, const char[] prop, float value, int element) { SetEntPropFloat(entity, type, prop, value, element); }
public int public_GetEntPropEnt(int entity, PropType type, const char[] prop, int element) { return GetEntPropEnt(entity, type, prop, element); }
public void public_SetEntPropEnt(int entity, PropType type, const char[] prop, int other, int element) { SetEntPropEnt(entity, type, prop, other, element); }
public void public_GetEntPropVector(int entity, PropType type, const char[] prop, float vec[3], int element) { GetEntPropVector(entity, type, prop, vec, element); }
public void public_SetEntPropVector(int entity, PropType type, const char[] prop, const float vec[3], int element) { SetEntPropVector(entity, type, prop, vec, element); }
public int public_GetEntPropString(int entity, PropType type, const char[] prop, char[] buffer, int maxlen, int element) { return GetEntPropString(entity, type, prop, buffer, maxlen, element); }
public int public_SetEntPropString(int entity, PropType type, const char[] prop, const char[] buffer, int element) { return SetEntPropString(entity, type, prop, buffer, element); }
public int public_GetEntPropArraySize(int entity, PropType type, const char[] prop) { return GetEntPropArraySize(entity, type, prop); }
public Address public_GetEntityAddress(int entity) { return GetEntityAddress(entity); }

/* SDKTOOLS_FUNCTIONS.INC */
// SDKTOOLS_FUNCTIONS.INC - Public
public bool public_RemovePlayerItem(int client, int item) { return RemovePlayerItem(client, item); }
public int public_GivePlayerItem(int client, const char[] item, int iSubType) { return GivePlayerItem(client, item, iSubType); }
public int public_GetPlayerWeaponSlot(int client, int slot) { return GetPlayerWeaponSlot(client, slot); }
public void public_IgniteEntity(int entity, float time, bool npc, float size, bool level) { IgniteEntity(entity, time, npc, size, level); }
public void public_ExtinguishEntity(int entity) { ExtinguishEntity(entity); }
public void public_TeleportEntity(int entity, const float origin[3], const float angles[3], const float velocity[3]) { TeleportEntity(entity, origin, angles, velocity); }
public void public_ForcePlayerSuicide(int client) { ForcePlayerSuicide(client); }
public void public_SlapPlayer(int client, int health, bool sound) { SlapPlayer(client, health, sound); }
public int public_FindEntityByClassname(int startEnt, const char[] classname) { return FindEntityByClassname(startEnt, classname); }
public bool public_GetClientEyeAngles(int client, float ang[3]) { return GetClientEyeAngles(client, ang); }
public int public_CreateEntityByName(const char[] classname, int ForceEdictIndex) { return CreateEntityByName(classname, ForceEdictIndex); }
public bool public_DispatchSpawn(int entity) { return DispatchSpawn(entity); }
public bool public_DispatchKeyValue(int entity, const char[] keyName, const char[] value) { return DispatchKeyValue(entity, keyName, value); }
public bool public_DispatchKeyValueFloat(int entity, const char[] keyName, float value) { return DispatchKeyValueFloat(entity, keyName, value); }
public bool public_DispatchKeyValueVector(int entity, const char[] keyName, const float vec[3]) { return DispatchKeyValueVector(entity, keyName, vec); }
public int public_GetClientAimTarget(int client, bool only_clients) { return GetClientAimTarget(client, only_clients); }
public int public_GetTeamCount() { return GetTeamCount(); }
public void public_GetTeamName(int index, char[] name, int maxlength) { GetTeamName(index, name, maxlength); }
public int public_GetTeamScore(int index) { return GetTeamScore(index); }
public void public_SetTeamScore(int index, int value) { SetTeamScore(index, value); }
public int public_GetTeamClientCount(int index) { return GetTeamClientCount(index); }
public int public_GetTeamEntity(int teamIndex) { return GetTeamEntity(teamIndex); }
public void public_SetEntityModel(int entity, const char[] model) { SetEntityModel(entity, model); }
public bool public_GetPlayerDecalFile(int client, char[] hex, int maxlength) { return GetPlayerDecalFile(client, hex, maxlength); }
public bool public_GetPlayerJingleFile(int client, char[] hex, int maxlength) { return GetPlayerJingleFile(client, hex, maxlength); }
public void public_GetServerNetStats(float &inAmount, float &outAmount) { GetServerNetStats(inAmount, outAmount); }
public void public_EquipPlayerWeapon(int client, int weapon) { EquipPlayerWeapon(client, weapon); }
public void public_ActivateEntity(int entity) { ActivateEntity(entity); }
public void public_SetClientInfo(int client, const char[] key, const char[] value) { SetClientInfo(client, key, value); }
public void public_SetClientName(int client, const char[] name) { SetClientName(client, name); }
public int public_GivePlayerAmmo(int client, int amount, int ammotype, bool suppressSound) { return GivePlayerAmmo(client, amount, ammotype, suppressSound); }

/* SDKTOOLS_HOOKS.INC */
// SDKTOOLS_HOOKS.INC - Natives
public Action OnPlayerRunCmd(int client, int &buttons, int &impulse, float vel[3], float angles[3], int &weapon, int &subtype, int &cmdnum, int &tickcount, int &seed, int mouse[2])
{
	return native_OnPlayerRunCmd(client, buttons, impulse, vel, angles, weapon, subtype, cmdnum, tickcount, seed, mouse);
}
public void OnPlayerRunCmdPost(int client, int buttons, int impulse, const float vel[3], const float angles[3], int weapon, int subtype, int cmdnum, int tickcount, int seed, const int mouse[2])
{
	native_OnPlayerRunCmdPost(client, buttons, impulse, vel, angles, weapon, subtype, cmdnum, tickcount, seed, mouse);
}

/* SDKHOOKS.INC */
// Helper
stock SDKHookCB ResolveCallback(SDKHookType type)
{
	return s_SDKHookCallbacks[type];
}
// SDKHOOKS.INC - Natives
public void OnEntityCreated(int entity, const char[] classname) { native_OnEntityCreated(entity, classname); }
public void OnEntitySpawned(int entity, const char[] classname) { native_OnEntitySpawned(entity, classname); }
public void OnEntityDestroyed(int entity) { native_OnEntityDestroyed(entity); }
public Action OnGetGameDescription(char gameDesc[64]) { return native_OnGetGameDescription(gameDesc); }
public Action OnLevelInit(const char[] mapName, char mapEntities[2097152]) { return native_OnLevelInit(mapName, mapEntities); }
// SDKHOOKS.INC - Public
public void public_SDKHook(int entity, SDKHookType type) { SDKHook(entity, type, ResolveCallback(type)); }
public bool public_SDKHookEx(int entity, SDKHookType type) { return SDKHookEx(entity, type, ResolveCallback(type)); }
public void public_SDKUnhook(int entity, SDKHookType type) { SDKUnhook(entity, type, ResolveCallback(type)); }
public void public_SDKHooks_TakeDamage(int entity, int inflictor, int attacker,
		float damage, int damageType, int weapon,
		const float damageForce[3], const float damagePosition[3])
		{ SDKHooks_TakeDamage(entity, inflictor, attacker, damage, damageType, weapon, damageForce, damagePosition); }
public void public_SDKHooks_DropWeapon(int client, int weapon, const float vecTarget[3],
		const float vecVelocity[3])
		{ SDKHooks_DropWeapon(client, weapon, vecTarget, vecVelocity); }

// MENUS.INC
public Menu public_CreateMenu(MenuAction actions) { return CreateMenu(MenuHandlerCallback, actions); }
public bool public_DisplayMenu(Handle menu, int client, int time) { return DisplayMenu(menu, client, time); }
public bool public_DisplayMenuAtItem(Handle menu, int client, int first_item, int time) { return DisplayMenuAtItem(menu, client, first_item, time); }
public bool public_AddMenuItem(Handle menu, const char[] info, const char[] display, int style) { return AddMenuItem(menu, info, display, style); }
public bool public_InsertMenuItem(Handle menu, int position, const char[] info, const char[] display, int style) { return InsertMenuItem(menu, position, info, display, style); }
public bool public_RemoveMenuItem(Handle menu, int position) { return RemoveMenuItem(menu, position); }
public void public_RemoveAllMenuItems(Handle menu) { RemoveAllMenuItems(menu); }
public bool public_GetMenuItem(Handle menu, int position, char[] infoBuf, int infoBufLen, int &style, char[] dispBuf, int dispBufLen, int client)
	{ return GetMenuItem(menu, position, infoBuf, infoBufLen, style, dispBuf, dispBufLen, client); }
public void public_MenuShufflePerClient(Handle menu, int start, int stop) { MenuShufflePerClient(menu, start, stop); }
public void public_MenuSetClientMapping(Handle menu, int client, int[] array, int length) { MenuSetClientMapping(menu, client, array, length); }
public int public_GetMenuSelectionPosition() { return GetMenuSelectionPosition(); }
public int public_GetMenuItemCount(Handle menu) { return GetMenuItemCount(menu); }
public bool public_SetMenuPagination(Handle menu, int itemsPerPage) { return SetMenuPagination(menu, itemsPerPage); }
public int public_GetMenuPagination(Handle menu) { return GetMenuPagination(menu); }
public Handle public_GetMenuStyle(Handle menu) { return GetMenuStyle(menu); }
public void public_SetMenuTitle(Handle menu, const char[] fmt, any...) { char buffer[128]; VFormat(buffer, sizeof(buffer), fmt, 3); SetMenuTitle(menu, buffer); }
public int public_GetMenuTitle(Handle menu, char[] buffer, int maxlength) { return GetMenuTitle(menu, buffer, maxlength); }
public Panel public_CreatePanelFromMenu(Handle menu) { return CreatePanelFromMenu(menu); }
public bool public_GetMenuExitButton(Handle menu) { return GetMenuExitButton(menu); }
public bool public_SetMenuExitButton(Handle menu, bool button) { return SetMenuExitButton(menu, button); }
public bool public_GetMenuExitBackButton(Handle menu) { return GetMenuExitBackButton(menu); }
public void public_SetMenuExitBackButton(Handle menu, bool button) { SetMenuExitBackButton(menu, button); }
public bool public_SetMenuNoVoteButton(Handle menu, bool button) { return SetMenuNoVoteButton(menu, button); }
public void public_CancelMenu(Handle menu) { CancelMenu(menu); }
public int public_GetMenuOptionFlags(Handle menu) { return GetMenuOptionFlags(menu); }
public void public_SetMenuOptionFlags(Handle menu, int flags) { SetMenuOptionFlags(menu, flags); }
public bool public_IsVoteInProgress(Handle menu) { return IsVoteInProgress(menu); }
public void public_CancelVote() { CancelVote(); }
public bool public_VoteMenu(Handle menu, int[] clients, int numClients, int time, int flags) { return VoteMenu(menu, clients, numClients, time, flags); }
/*stock bool VoteMenuToAll(Handle menu, int time, int flags)
{
	int total;
	int[] players = new int[MaxClients];

	for (int i=1; i<=MaxClients; i++)
	{
		if (!IsClientInGame(i) || IsFakeClient(i))
		{
			continue;
		}
		players[total++] = i;
	}

	return VoteMenu(menu, players, total, time, flags);
}*/
public void public_SetVoteResultCallback(Handle menu) { SetVoteResultCallback(menu, VoteHandlerCallback); }
public int public_CheckVoteDelay() { return CheckVoteDelay(); }
public bool public_IsClientInVotePool(int client) { return IsClientInVotePool(client); }
public bool public_RedrawClientVoteMenu(int client, bool revotes) { return RedrawClientVoteMenu(client, revotes); }
public Handle public_GetMenuStyleHandle(MenuStyle style) { return GetMenuStyleHandle(style); }
public Panel public_CreatePanel(Handle hStyle) { return CreatePanel(hStyle); }
public Menu public_CreateMenuEx(Handle hStyle, MenuAction actions) { return CreateMenuEx(hStyle, MenuHandlerCallback, actions); }
public MenuSource public_GetClientMenu(int client, Handle hStyle) { return GetClientMenu(client, hStyle); }
public bool public_CancelClientMenu(int client, bool autoIgnore, Handle hStyle) { return CancelClientMenu(client, autoIgnore, hStyle); }
public int public_GetMaxPageItems(Handle hStyle) { return GetMaxPageItems(hStyle); }
public Handle public_GetPanelStyle(Handle panel) { return GetPanelStyle(panel); }
public void public_SetPanelTitle(Handle panel, const char[] text, bool onlyIfEmpty) { SetPanelTitle(panel, text, onlyIfEmpty); }
public int public_DrawPanelItem(Handle panel, const char[] text, int style) { return DrawPanelItem(panel, text, style); }
public bool public_DrawPanelText(Handle panel, const char[] text) { return DrawPanelText(panel, text); }
public bool public_CanPanelDrawFlags(Handle panel, int style) { return CanPanelDrawFlags(panel, style); }
public bool public_SetPanelKeys(Handle panel, int keys) { return SetPanelKeys(panel, keys); }
public bool public_SendPanelToClient(Handle panel, int client, int time) { return SendPanelToClient(panel, client, MenuHandlerCallback, time); }
public int public_GetPanelTextRemaining(Handle panel) { return GetPanelTextRemaining(panel); }
public int public_GetPanelCurrentKey(Handle panel) { return GetPanelCurrentKey(panel); }
public bool public_SetPanelCurrentKey(Handle panel, int key) { return SetPanelCurrentKey(panel, key); }
public int public_RedrawMenuItem(const char[] text) { return RedrawMenuItem(text); }
public bool public_InternalShowMenu(int client, const char[] str, int time, int keys) { return InternalShowMenu(client, str, time, keys, MenuHandlerCallback); }

/*stock void GetMenuVoteInfo(int param2, int &winningVotes, int &totalVotes)
{
	winningVotes = param2 & 0xFFFF;
	totalVotes = param2 >> 16;
}*/

/*stock bool IsNewVoteAllowed()
{
	if (IsVoteInProgress() || CheckVoteDelay() != 0)
	{
		return false;
	}

	return true;
}*/

/* EVENTS.INC */
// EVENTS.INC - Public
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
