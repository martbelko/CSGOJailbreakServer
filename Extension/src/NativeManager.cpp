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

cell_t NativeManager::CMDCallback(IPluginContext* pContext, const cell_t* params)
{
	int client = params[1];
	char* cmd;
	pContext->LocalToString(params[2], &cmd);
	char* args;
	pContext->LocalToString(params[3], &args);

	return MainPlugin::CMDCallback(client, cmd, args);
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
