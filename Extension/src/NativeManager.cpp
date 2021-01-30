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

cell_t NativeManager::OnRoundStartPre(IPluginContext* pContext, const cell_t* params)
{
	MainPlugin::OnRoundStartPre();
	return 0;
}

cell_t NativeManager::OnRoundStartPost(IPluginContext* pContext, const cell_t* params)
{
	MainPlugin::OnRoundStartPost();
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
	int kv = params[2];
	return MainPlugin::OnClientCommandKeyValues(client, kv);
}

int NativeManager::OnClientCommandKeyValuesPost(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	int kv = params[2];
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
