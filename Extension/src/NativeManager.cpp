#include "NativeManager.h"

#include "PublicManager.h"
#include "MainPlugin.h"

cell_t NativeManager::OnPluginStart(IPluginContext* pContext, const cell_t* params)
{
	PublicManager::InitOnPluginStart(pContext);
	MainPlugin::OnPluginStart();
	return 0;
}

cell_t NativeManager::OnPluginEnd(IPluginContext* pContext, const cell_t* params)
{
	MainPlugin::OnPluginEnd();
	return 0;
}

cell_t NativeManager::OnMapStart(IPluginContext* pContext, const cell_t* params)
{
	return 0;
}

cell_t NativeManager::OnMapEnd(IPluginContext* pContext, const cell_t* params)
{
	return 0;
}

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
