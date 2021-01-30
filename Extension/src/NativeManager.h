#pragma once

#include "smsdk_ext.h"

#include "Defines.h"

class NativeManager
{
public:
	static cell_t OnPluginStart(IPluginContext* pContext, const cell_t* params);
	static cell_t OnPluginEnd(IPluginContext* pContext, const cell_t* params);

	static cell_t OnMapStart(IPluginContext* pContext, const cell_t* params);
	static cell_t OnMapEnd(IPluginContext* pContext, const cell_t* params);

	static cell_t OnRoundStartPre(IPluginContext* pContext, const cell_t* params);
	static cell_t OnRoundStartPost(IPluginContext* pContext, const cell_t* params);

	static cell_t ConCmdCallback(IPluginContext* pContext, const cell_t* params);
	static cell_t SrvCmdCallback(IPluginContext* pContext, const cell_t* params);
	static cell_t CmdListenerCallback(IPluginContext* pContext, const cell_t* params);

	// cstrike.inc
	static int CS_OnBuyCommand(IPluginContext* pContext, const cell_t* params);
	static int CS_OnCSWeaponDrop(IPluginContext* pContext, const cell_t* params);
	static int CS_OnGetWeaponPrice(IPluginContext* pContext, const cell_t* params);
	static int CS_OnTerminateRound(IPluginContext* pContext, const cell_t* params);

	// Console.inc
	static int OnClientSayCommand(IPluginContext* pContext, const cell_t* params);
	static int OnClientSayCommandPost(IPluginContext* pContext, const cell_t* params);

	// Client.inc
	static int OnClientConnect(IPluginContext* pContext, const cell_t* params);
	static int OnClientConnected(IPluginContext* pContext, const cell_t* params);
	static int OnClientPutInServer(IPluginContext* pContext, const cell_t* params);
	static int OnClientDisconnect(IPluginContext* pContext, const cell_t* params);
	static int OnClientDisconnectPost(IPluginContext* pContext, const cell_t* params);
	static int OnClientCommand(IPluginContext* pContext, const cell_t* params);
	static int OnClientCommandKeyValues(IPluginContext* pContext, const cell_t* params);
	static int OnClientCommandKeyValuesPost(IPluginContext* pContext, const cell_t* params);
	static int OnClientSettingsChanged(IPluginContext* pContext, const cell_t* params);
	static int OnClientAuthorized(IPluginContext* pContext, const cell_t* params);
	static int OnClientPreAdminCheck(IPluginContext* pContext, const cell_t* params);
	static int OnClientPostAdminFilter(IPluginContext* pContext, const cell_t* params);
	static int OnClientPostAdminCheck(IPluginContext* pContext, const cell_t* params);
};
