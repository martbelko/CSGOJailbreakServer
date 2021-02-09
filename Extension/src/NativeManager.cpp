#include "NativeManager.h"

#include "PublicManager.h"
#include "MainPlugin.h"

cell_t NativeManager::ConCmdCallback(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	char* cmd;
	pContext->LocalToString(params[2], &cmd);
	char* args;
	pContext->LocalToString(params[3], &args);

	return MainPlugin::ConCmdCallback(client, cmd, args);
}

cell_t NativeManager::SrvCmdCallback(IPluginContext* pContext, const cell_t* params)
{
	char* cmd;
	pContext->LocalToString(params[1], &cmd);
	char* args;
	pContext->LocalToString(params[2], &args);

	return MainPlugin::SrvCmdCallback(cmd, args);
}

cell_t NativeManager::CmdListenerCallback(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	char* cmd;
	pContext->LocalToString(params[2], &cmd);
	int argc = params[3];

	return MainPlugin::CmdListenerCallback(client, cmd, argc);
}

int NativeManager::OnPlayerRunCmd(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];

	int* buttonsPtr;
	pContext->LocalToPhysAddr(params[2], &buttonsPtr);

	int* impulsePtr;
	pContext->LocalToPhysAddr(params[3], &impulsePtr);

	int* velocityPtr;
	pContext->LocalToPhysAddr(params[4], &velocityPtr);
	float velocity[3] = { sp_ctof(velocityPtr[0]), sp_ctof(velocityPtr[1]), sp_ctof(velocityPtr[2]) };

	int* anglesPtr;
	pContext->LocalToPhysAddr(params[5], &anglesPtr);
	float angles[3] = { sp_ctof(anglesPtr[0]), sp_ctof(anglesPtr[1]), sp_ctof(anglesPtr[2]) };

	int* weaponPtr;
	pContext->LocalToPhysAddr(params[6], &weaponPtr);

	int* subTypePtr;
	pContext->LocalToPhysAddr(params[7], &subTypePtr);

	int* cmdNumPtr;
	pContext->LocalToPhysAddr(params[8], &cmdNumPtr);

	int* tickCountPtr;
	pContext->LocalToPhysAddr(params[9], &tickCountPtr);

	int* seedPtr;
	pContext->LocalToPhysAddr(params[10], &seedPtr);

	int* mousePtr;
	pContext->LocalToPhysAddr(params[11], &mousePtr);

	Action res = MainPlugin::OnPlayerRunCmd(client, *buttonsPtr, *impulsePtr, velocity,
		angles, *weaponPtr, *subTypePtr, *cmdNumPtr, *tickCountPtr, *seedPtr, mousePtr);

	anglesPtr[0] = angles[0];
	anglesPtr[1] = angles[1];
	anglesPtr[2] = angles[2];

	velocityPtr[0] = velocity[0];
	velocityPtr[1] = velocity[1];
	velocityPtr[2] = velocity[2];

	return res;
}

int NativeManager::OnPlayerRunCmdPost(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	int buttons = params[2];
	int impulse = params[3];

	int* velocityPtr;
	pContext->LocalToPhysAddr(params[4], &velocityPtr);
	const float velocity[3] = { sp_ctof(velocityPtr[0]), sp_ctof(velocityPtr[1]), sp_ctof(velocityPtr[2]) };

	int* anglesPtr;
	pContext->LocalToPhysAddr(params[5], &anglesPtr);
	const float angles[3] = { sp_ctof(anglesPtr[0]), sp_ctof(anglesPtr[1]), sp_ctof(anglesPtr[2]) };

	int weapon = params[6];
	int subType = params[7];
	int cmdnum = params[8];
	int tickCount = params[9];
	int seed = params[10];

	int* mousePtr;
	pContext->LocalToPhysAddr(params[11], &mousePtr);

	MainPlugin::OnPlayerRunCmdPost(client, buttons, impulse, velocity, angles,
		weapon, subType, cmdnum, tickCount, seed, mousePtr);
	return 0;
}

int NativeManager::OnFileSend(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	char* filepath;
	pContext->LocalToString(params[2], &filepath);

	return MainPlugin::OnFileSend(client, filepath);
}

int NativeManager::OnFileReceive(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	char* filepath;
	pContext->LocalToString(params[2], &filepath);

	return MainPlugin::OnFileReceive(client, filepath);
}

int NativeManager::OnEntityCreated(IPluginContext* pContext, const cell_t* params)
{
	int entity = params[1];
	char* className;
	pContext->LocalToString(params[2], &className);
	MainPlugin::OnEntityCreated(entity, className);
	return 0;
}

int NativeManager::OnEntitySpawned(IPluginContext* pContext, const cell_t* params)
{
	int entity = params[1];
	char* className;
	pContext->LocalToString(params[2], &className);
	MainPlugin::OnEntitySpawned(entity, className);
	return 0;
}

int NativeManager::OnEntityDestroyed(IPluginContext* pContext, const cell_t* params)
{
	int entity = params[1];
	MainPlugin::OnEntityDestroyed(entity);
	return 0;
}

int NativeManager::OnGetGameDescription(IPluginContext* pContext, const cell_t* params)
{
	char* gameDesc;
	pContext->LocalToString(params[1], &gameDesc);
	return MainPlugin::OnGetGameDescription(gameDesc);
}

int NativeManager::OnLevelInit(IPluginContext* pContext, const cell_t* params)
{
	char* mapName;
	pContext->LocalToString(params[1], &mapName);
	char* mapEntities;
	pContext->LocalToString(params[2], &mapEntities);
	return MainPlugin::OnLevelInit(mapName, mapEntities);
}

int NativeManager::SDKHooksCallback1(SDKHookType type, IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	SDKHooksCallback1Func callback = static_cast<SDKHooksCallback1Func>(PublicManager::s_SDKHooksCallbacks[std::make_pair(params[1], type)]);
	callback(client);
	return 0;
}

int NativeManager::SDKHooksCallback2(SDKHookType type, IPluginContext* pContext, const cell_t* params)
{
	int entity = params[1];
	SDKHooksCallback2Func callback = static_cast<SDKHooksCallback2Func>(PublicManager::s_SDKHooksCallbacks[std::make_pair(params[1], type)]);
	return callback(entity);
}

int NativeManager::SDKHooksCallback3(SDKHookType type, IPluginContext* pContext, const cell_t* params)
{
	int entity = params[1];
	int other = params[2];
	SDKHooksCallback3Func callback = static_cast<SDKHooksCallback3Func>(PublicManager::s_SDKHooksCallbacks[std::make_pair(params[1], type)]);
	return callback(entity, other);
}

int NativeManager::SDKHooksCallback4(SDKHookType type, IPluginContext* pContext, const cell_t* params)
{
	int entity = params[1];
	int other = params[2];
	SDKHooksCallback4Func callback = static_cast<SDKHooksCallback4Func>(PublicManager::s_SDKHooksCallbacks[std::make_pair(params[1], type)]);
	callback(entity, other);
	return 0;
}

int NativeManager::SDKHooksCallback5(SDKHookType type, IPluginContext* pContext, const cell_t* params)
{
	int entity = params[1];
	int* maxHealthAddr;
	pContext->LocalToPhysAddr(params[2], &maxHealthAddr);

	SDKHooksCallback5Func callback = static_cast<SDKHooksCallback5Func>(PublicManager::s_SDKHooksCallbacks[std::make_pair(params[1], type)]);
	return callback(entity, *maxHealthAddr);
}

int NativeManager::SDKHooksCallback6(SDKHookType type, IPluginContext* pContext, const cell_t* params)
{
	int victim = params[1];

	int* attackerAddr;
	pContext->LocalToPhysAddr(params[2], &attackerAddr);

	int* inflictorAddr;
	pContext->LocalToPhysAddr(params[3], &inflictorAddr);

	int* damageAddr;
	pContext->LocalToPhysAddr(params[4], &damageAddr);
	float damage = sp_ctof(*damageAddr);

	int* damageTypeAddr;
	pContext->LocalToPhysAddr(params[5], &damageTypeAddr);

	int* weaponAddr;
	pContext->LocalToPhysAddr(params[6], &weaponAddr);

	int* damageForceAddr;
	pContext->LocalToPhysAddr(params[7], &damageForceAddr);
	float damageForce[3] = { sp_ctof(damageForceAddr[0]), sp_ctof(damageForceAddr[1]), sp_ctof(damageForceAddr[2]) };

	int* damagePositionAddr;
	pContext->LocalToPhysAddr(params[8], &damagePositionAddr);
	float damagePosition[3] = { sp_ctof(damagePositionAddr[0]), sp_ctof(damagePositionAddr[1]), sp_ctof(damagePositionAddr[2]) };

	int damageCustom = params[9];

	SDKHooksCallback6Func callback = static_cast<SDKHooksCallback6Func>(PublicManager::s_SDKHooksCallbacks[std::make_pair(params[1], type)]);
	Action res = callback(victim, *attackerAddr, *inflictorAddr, damage, *damageTypeAddr, *weaponAddr, damageForce, damagePosition, damageCustom);

	damagePositionAddr[0] = sp_ftoc(damagePosition[0]);
	damagePositionAddr[1] = sp_ftoc(damagePosition[1]);
	damagePositionAddr[2] = sp_ftoc(damagePosition[2]);

	damageForceAddr[0] = sp_ftoc(damageForce[0]);
	damageForceAddr[1] = sp_ftoc(damageForce[1]);
	damageForceAddr[2] = sp_ftoc(damageForce[2]);

	*damageAddr = sp_ftoc(damage);

	return res;
}

int NativeManager::SDKHooksCallback7(SDKHookType type, IPluginContext* pContext, const cell_t* params)
{
	int victim = params[1];

	int attacker = params[2];

	int inflictor = params[3];

	float damage = sp_ctof(params[4]);

	int damageType = params[5];

	int weapon = params[6];

	int* damageForceAddr;
	pContext->LocalToPhysAddr(params[7], &damageForceAddr);
	float damageForce[3] = { sp_ctof(damageForceAddr[0]), sp_ctof(damageForceAddr[1]), sp_ctof(damageForceAddr[2]) };

	int* damagePositionAddr;
	pContext->LocalToPhysAddr(params[8], &damagePositionAddr);
	float damagePosition[3] = { sp_ctof(damagePositionAddr[0]), sp_ctof(damagePositionAddr[1]), sp_ctof(damagePositionAddr[2]) };

	int damageCustom = params[9];

	SDKHooksCallback7Func callback = static_cast<SDKHooksCallback7Func>(PublicManager::s_SDKHooksCallbacks[std::make_pair(params[1], type)]);
	callback(victim, attacker, inflictor, damage, damageType, weapon, damageForce, damagePosition, damageCustom);
	return 0;
}

int NativeManager::SDKHooksCallback8(SDKHookType type, IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	int shots = params[2];
	char* weaponName;
	pContext->LocalToString(params[3], &weaponName);

	SDKHooksCallback8Func callback = static_cast<SDKHooksCallback8Func>(PublicManager::s_SDKHooksCallbacks[std::make_pair(params[1], type)]);
	callback(client, shots, weaponName);
	return 0;
}

int NativeManager::SDKHooksCallback9(SDKHookType type, IPluginContext* pContext, const cell_t* params)
{
	int victim = params[1];

	int* attackerAddr;
	pContext->LocalToPhysAddr(params[2], &attackerAddr);

	int* inflictorAddr;
	pContext->LocalToPhysAddr(params[3], &inflictorAddr);

	int* damageAddr;
	pContext->LocalToPhysAddr(params[4], &damageAddr);
	float damage = sp_ctof(*damageAddr);

	int* damageTypeAddr;
	pContext->LocalToPhysAddr(params[5], &damageTypeAddr);

	int* ammoTypeAddr;
	pContext->LocalToPhysAddr(params[6], &ammoTypeAddr);

	int hitbox = params[7];

	int hitgroup = params[8];

	rootconsole->ConsolePrint("Trying to take damage %f", damage);
	SDKHooksCallback9Func callback = static_cast<SDKHooksCallback9Func>(PublicManager::s_SDKHooksCallbacks[std::make_pair(params[1], type)]);
	Action res = callback(victim, *attackerAddr, *inflictorAddr, damage, *damageTypeAddr, *ammoTypeAddr, hitbox, hitgroup);
	rootconsole->ConsolePrint("Trying to take new damage %f", damage);

	*damageAddr = sp_ftoc(damage);

	return res;
}

int NativeManager::SDKHooksCallback10(SDKHookType type, IPluginContext* pContext, const cell_t* params)
{
	int victim = params[1];
	int attacker = params[2];
	int inflictor = params[3];
	float damage = sp_ctof(params[4]);
	int damageType = params[5];
	int ammoType = params[6];
	int hitbox = params[7];
	int hitgroup = params[8];

	SDKHooksCallback10Func callback = static_cast<SDKHooksCallback10Func>(PublicManager::s_SDKHooksCallbacks[std::make_pair(params[1], type)]);
	callback(victim, attacker, inflictor, damage, damageType, ammoType, hitbox, hitgroup);
	return 0;
}

int NativeManager::SDKHooksCallback11(SDKHookType type, IPluginContext* pContext, const cell_t* params)
{
	int entity = params[1];
	int collisionGroup = params[2];
	int contentsMask = params[3];
	bool originalResult = params[4];
	SDKHooksCallback11Func callback = static_cast<SDKHooksCallback11Func>(PublicManager::s_SDKHooksCallbacks[std::make_pair(params[1], type)]);
	return callback(entity, collisionGroup, contentsMask, originalResult);
}

int NativeManager::SDKHooksCallback12(SDKHookType type, IPluginContext* pContext, const cell_t* params)
{
	int entity = params[1];
	int activator = params[2];
	int caller = params[3];
	UseType useType = static_cast<UseType>(params[4]);
	float value = sp_ctof(params[5]);
	SDKHooksCallback12Func callback = static_cast<SDKHooksCallback12Func>(PublicManager::s_SDKHooksCallbacks[std::make_pair(params[1], type)]);
	return callback(entity, activator, caller, useType, value);
}

int NativeManager::SDKHooksCallback13(SDKHookType type, IPluginContext* pContext, const cell_t* params)
{
	int entity = params[1];
	int activator = params[2];
	int caller = params[3];
	UseType useType = static_cast<UseType>(params[4]);
	float value = sp_ctof(params[5]);
	SDKHooksCallback13Func callback = static_cast<SDKHooksCallback13Func>(PublicManager::s_SDKHooksCallbacks[std::make_pair(params[1], type)]);
	callback(entity, activator, caller, useType, value);
	return 0;
}

int NativeManager::SDKHooksCallback14(SDKHookType type, IPluginContext* pContext, const cell_t* params)
{
	int weapon = params[1];
	int successful = params[2];
	SDKHooksCallback14Func callback = static_cast<SDKHooksCallback14Func>(PublicManager::s_SDKHooksCallbacks[std::make_pair(params[1], type)]);
	callback(weapon, successful);
	return 0;
}

int NativeManager::SDKHooksCallback15(SDKHookType type, IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	bool origRet = params[2];
	SDKHooksCallback15Func callback = static_cast<SDKHooksCallback15Func>(PublicManager::s_SDKHooksCallbacks[std::make_pair(params[1], type)]);
	return callback(client, origRet);
}

int NativeManager::MenuHandlerCallback(IPluginContext* pContext, const cell_t* params)
{
	MenuHandle menu = params[1];
	MenuAction action = static_cast<MenuAction>(params[2]);
	int param1 = params[3];
	int param2 = params[4];

	MenuHandler handler = PublicManager::s_MenuHandlers[menu];
	return handler(menu, action, param1, param2);
}

int NativeManager::VoteHandlerCallback(IPluginContext* pContext, const cell_t* params)
{
	MenuHandle menu = params[1];
	int numVotes = params[2];
	int numClients = params[3];
	const int** clientInfo;
	pContext->LocalToPhysAddr(params[4], reinterpret_cast<int**>(&clientInfo));
	int numItems = params[5];
	const int** itemInfo;
	pContext->LocalToPhysAddr(params[6], reinterpret_cast<int**>(&itemInfo));

	VoteHandler handler = PublicManager::s_VoteHandlers[menu];
	handler(menu, numVotes, numClients, clientInfo, numItems, itemInfo);
	return 0;
}

int NativeManager::EventHookCallbackPre(IPluginContext* pContext, const cell_t* params)
{
	EventHandle eventHandle = params[1];
	char* name;
	pContext->LocalToString(params[2], &name);
	bool dontBroadcast = params[3];

	EventHookCallback callbackFunc = PublicManager::s_EventHookCallbacksPre[name];
	return callbackFunc(eventHandle, name, dontBroadcast);
}

int NativeManager::EventHookCallbackPost(IPluginContext* pContext, const cell_t* params)
{
	EventHandle eventHandle = params[1];
	char* name;
	pContext->LocalToString(params[2], &name);
	bool dontBroadcast = params[3];

	EventHookCallback callbackFunc = PublicManager::s_EventHookCallbacksPost[name];
	return callbackFunc(eventHandle, name, dontBroadcast);
}

int NativeManager::EventHookCallbackPostNoCopy(IPluginContext* pContext, const cell_t* params)
{
	EventHandle eventHandle = params[1];
	char* name;
	pContext->LocalToString(params[2], &name);
	bool dontBroadcast = params[3];

	EventHookCallback callbackFunc = PublicManager::s_EventHookCallbacksPostNoCopy[name];
	return callbackFunc(eventHandle, name, dontBroadcast);
}

int NativeManager::SQLTxnSuccessCallback(IPluginContext* pContext, const cell_t* params)
{
	return 0;
}

int NativeManager::SQLTxnFailureCallback(IPluginContext* pContext, const cell_t* params)
{
	return 0;
}

int NativeManager::SQLTCallbackConnect(IPluginContext* pContext, const cell_t* params)
{
	Handle owner = params[1];
	Handle hndl = params[2];
	char* error;
	pContext->LocalToString(params[3], &error);
	int index = params[4]; // Index from PublicManager

	auto& dataMap = PublicManager::s_SQLTConnectCallbacksData;
	auto& callbackMap = PublicManager::s_SQLTConnectCallbacks;
	int data = dataMap[index];
	auto func = callbackMap[index];

	func(owner, hndl, error, data);
	return 0;
}

int NativeManager::SQLTCallbackQuery(IPluginContext* pContext, const cell_t* params)
{
	Handle owner = params[1];
	Handle hndl = params[2];
	char* error;
	pContext->LocalToString(params[3], &error);
	int index = params[4]; // Index from PublicManager

	auto& dataMap = PublicManager::s_SQLTQueryCallbacksData;
	auto& callbackMap = PublicManager::s_SQLTQueryCallbacks;
	int data = dataMap[index];
	auto func = callbackMap[index];

	func(owner, hndl, error, data);
	return 0;
}

/////////////////
/* CSTIKE.INC */
/////////////////

int NativeManager::CS_OnBuyCommand(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	char* weapon;
	pContext->LocalToString(params[2], &weapon);
	return MainPlugin::CS_OnBuyCommand(client, weapon);
}

int NativeManager::CS_OnCSWeaponDrop(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	int weaponIndex = params[2];
	return MainPlugin::CS_OnCSWeaponDrop(client, weaponIndex);
}

int NativeManager::CS_OnGetWeaponPrice(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	char* weapon;
	pContext->LocalToString(params[2], &weapon);
	int* price;
	pContext->LocalToPhysAddr(params[3], &price);

	return MainPlugin::CS_OnGetWeaponPrice(client, weapon, *price);
}

int NativeManager::CS_OnTerminateRound(IPluginContext* pContext, const cell_t* params)
{
	int* delayAddr;
	pContext->LocalToPhysAddr(params[1], &delayAddr);
	float delay = sp_ctof(*delayAddr);

	CSRoundEndReason reason;
	pContext->LocalToPhysAddr(params[2], reinterpret_cast<int**>(&reason));

	int res = MainPlugin::CS_OnTerminateRound(delay, reason);
	*delayAddr = delay;
	return res;
}

/////////////////
/* CONSOLE.INC */
/////////////////

int NativeManager::OnClientSayCommand(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	char* command;
	pContext->LocalToString(params[2], &command);
	char* args;
	pContext->LocalToString(params[3], &args);

	return MainPlugin::OnClientSayCommand(client, command, args);
}

int NativeManager::OnClientSayCommandPost(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	char* command;
	pContext->LocalToString(params[2], &command);
	char* args;
	pContext->LocalToString(params[3], &args);

	MainPlugin::OnClientSayCommandPost(client, command, args);
	return 0;
}

////////////////
/* CLIENT.INC */
////////////////
int NativeManager::OnClientConnect(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	char* rejectMsg;
	pContext->LocalToString(params[2], &rejectMsg);
	int maxlen = params[3];

	return MainPlugin::OnClientConnect(client, rejectMsg, maxlen);
}

int NativeManager::OnClientConnected(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	MainPlugin::OnClientConnected(client);
	return 0;
}

int NativeManager::OnClientPutInServer(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	MainPlugin::OnClientPutInServer(client);
	return 0;
}

int NativeManager::OnClientDisconnect(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	MainPlugin::OnClientDisconnect(client);
	return 0;
}

int NativeManager::OnClientDisconnectPost(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	MainPlugin::OnClientDisconnectPost(client);
	return 0;
}

int NativeManager::OnClientCommand(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	int argc = params[2];
	return MainPlugin::OnClientCommand(client, argc);
}

int NativeManager::OnClientCommandKeyValues(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	KeyValuesHandle kv = params[2];
	return MainPlugin::OnClientCommandKeyValues(client, kv);
}

int NativeManager::OnClientCommandKeyValuesPost(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	KeyValuesHandle kv = params[2];
	MainPlugin::OnClientCommandKeyValuesPost(client, kv);
	return 0;
}

int NativeManager::OnClientSettingsChanged(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	MainPlugin::OnClientSettingsChanged(client);
	return 0;
}

int NativeManager::OnClientAuthorized(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	char* auth;
	pContext->LocalToString(params[2], &auth);
	MainPlugin::OnClientAuthorized(client, auth);
	return 0;
}

int NativeManager::OnClientPreAdminCheck(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	return MainPlugin::OnClientPreAdminCheck(client);
}

int NativeManager::OnClientPostAdminFilter(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	MainPlugin::OnClientPostAdminFilter(client);
	return 0;
}

int NativeManager::OnClientPostAdminCheck(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	MainPlugin::OnClientPostAdminCheck(client);
	return 0;
}
